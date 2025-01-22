#include "inc/ast/parse_func.h"
#include "inc/core/style.h"
#include "inc/core/func.h"
#include "inc/ast/priority.h"
#include "inc/ast/node/style_sheet.h"
#include "inc/ast/node/number_literal.h"
#include "inc/ast/node/string_literal.h"
#include "inc/ast/node/var_declare.h"
#include "inc/ast/node/call_variable.h"
#include "inc/ast/node/binary_expression.h"
#include <string.h>

void callParseNext(ParseContext *context, BOOL continueWith(ParseContext *)) {
    while (continueWith(context)) {
        Token *token = parseContextNext(context);
        switch (token->type) {
            case TT_Identifier:
                parseIdentifier(context);
                break;
            case TT_Logic:
            case TT_Operator:
                parseOperator(context);
                break;
            case TT_Brace:
                parseBrace(context);
                break;
            case TT_Bracket:
                parseBracket(context);
                break;
            case TT_Literal:
                parseLiteral(context);
                break;
            default:
                parseContextTermExpected(context);
                break;
        }
    }
}

void cleanParseContextStack(ParseContext *context) {
    if (context->root->type == NT_VarDeclare) {
        Token *token;
        Node *right, *left;
        if (!stackEmpty(context->tokenStack)) {
            stackPush(context->nodeStack, listRemoveLast(((VarDeclare *) context->root)->children));
            while (!stackEmpty(context->tokenStack)) {
                token = stackPop(context->tokenStack);
                right = stackPop(context->nodeStack);
                left = stackPop(context->nodeStack);
                if (right == NULL || left == NULL) {
                    break;
                }
                stackPush(context->nodeStack, binaryExpressionNew(token->value, left, right));
            }
        }
    }
    if (context->nodeStack->size > 1 || !stackEmpty(context->tokenStack)) {
        parseContextTermExpected(context);
    } else if (context->nodeStack->size == 1) {
        nodeAddChild(context->root, stackPop(context->nodeStack));
    }
}

BOOL doContinueEndWithSemicolon(ParseContext *context) {
    return parseContextHasNext(context) && parseContextPeekNext(context)->type != TT_Semicolon;
}

void continueEndWithSemicolon(ParseContext *context) {
    callParseNext(context, doContinueEndWithSemicolon);
    cleanParseContextStack(context);
    if (parseContextHasNext(context)) {
        parseContextNext(context);
    }
}

Node *findVariable(ParseContext *context, const char *name) {
    List *children;
    Node *node = context->root;
    while (node != NULL) {
        if (node->type == NT_StyleSheet) {
            children = ((StyleSheet *) node)->children;
        } else if (node->type == NT_VarDeclare) {
            children = ((VarDeclare *) node)->children;
        } else {
            children = NULL;
        }
        if (children != NULL) {
            for (int i = 0; i < children->size; ++i) {
                if (((Node *) children->values[i])->type == NT_VarDeclare
                    && strcmp(((VarDeclare *) children->values[i])->name, name) == 0) {
                    return children->values[i];
                }
            }
        }
        node = node->parent;
    }
    return NULL;
}

void startParse(ParseContext *context) {
    callParseNext(context, parseContextHasNext);
}

void parseIdentifier(ParseContext *context) {
    Token *identifier = parseContextPeekPre(context);
    if (context->root->type == NT_VarDeclare) {
        Node *var = findVariable(context, identifier->value);
        if (var == NULL) {
            parseContextMessage(context, "Cannot find variable");
            return;
        }
        CallVariable *callVariable = callVariableNew(identifier->value, var);
        nodeAddChild(context->root, (POINTER) callVariable);
        return;
    }
    if (parseContextPeekNext(context)->type == TT_Colon) {
        parseContextNext(context);
        VarDeclare *varDeclare = varDeclareNew(identifier->value);
        nodeAddChild(context->root, (POINTER) varDeclare);
        parseContextRunAsRoot(context, (POINTER) varDeclare, continueEndWithSemicolon);
        if (listEmpty(varDeclare->children)) {
            parseContextTermExpected(context);
        }
    }
}

void parseOperator(ParseContext *context) {
    Node *root = context->root;
    if (root->type == NT_VarDeclare) {
        if (listEmpty(((VarDeclare *) root)->children)) {
            parseContextTermExpected(context);
            return;
        }
        stackPush(context->nodeStack, listRemoveLast(((VarDeclare *) root)->children));
        Token *token;
        Node *right, *left;
        while (!stackEmpty(context->tokenStack) &&
               operatorPriority((token = stackPeek(context->tokenStack))->value) >=
               operatorPriority(parseContextPeekPre(context)->value)) {
            stackPop(context->tokenStack);
            right = stackPop(context->nodeStack);
            left = stackPop(context->nodeStack);
            if (right == NULL || left == NULL) {
                break;
            }
            stackPush(context->nodeStack, binaryExpressionNew(token->value, left, right));
        }
        stackPush(context->tokenStack, parseContextPeekPre(context));
    }
}

void parseBrace(ParseContext *context) {

}

void parseBracket(ParseContext *context) {
    Node *root = context->root;
    if (root->type == NT_VarDeclare) {
        if (parseContextPeekPre(context)->value[0] == '(') {
            stackPush(context->tokenStack, parseContextPeekPre(context));
        } else {
            Token *token;
            Node *right = listRemoveLast(((VarDeclare *) root)->children), *left;
            if (right == NULL) {
                parseContextTermExpected(context);
                return;
            }
            while (!stackEmpty(context->tokenStack) && (token = stackPop(context->tokenStack))->value[0] != '(') {
                left = stackPop(context->nodeStack);
                if (left == NULL) {
                    break;
                }
                right = (POINTER) binaryExpressionNew(token->value, left, right);
            }
            nodeAddChild(root, right);
            if (token->value[0] != '(') {
                parseContextTermExpected(context);
            }
        }
    }
}

void parseLiteral(ParseContext *context) {
    Token *token = parseContextPeekPre(context);
    double number = 0;
    if (charsToDouble(token->value, &number)) {
        NumberLiteral *numberLiteral = numberLiteralNew(token->value, number, NULL);
        nodeAddChild(context->root, (POINTER) numberLiteral);
        return;
    }
    const char *unit = NULL;
    int l2, l1 = (int) strlen(token->value);
    for (int i = 0; i < 16; ++i) {
        l2 = (int) strlen(STYLE_UNITS[i]);
        if (l1 > l2 && strcmp(token->value + l1 - l2, STYLE_UNITS[i]) == 0) {
            unit = STYLE_UNITS[i];
            break;
        }
    }
    if (unit != NULL && charsToDoubleByRange(token->value, 0, l1 - l2, &number)) {
        NumberLiteral *numberLiteral = numberLiteralNew(token->value, number, unit);
        nodeAddChild(context->root, (POINTER) numberLiteral);
        return;
    }
    StringLiteral *stringLiteral = stringLiteralNew(token->value);
    nodeAddChild(context->root, (POINTER) stringLiteral);
}

void endParse(ParseContext *context) {
    context->ast = NULL;
    context->message = NULL;
    parseContextDel(context);
}
