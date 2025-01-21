#include "inc/ast/parse_func.h"
#include "inc/ast/node_achiever.h"
#include "inc/core/style.h"
#include "inc/core/func.h"
#include "inc/ast/priority.h"
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
    Token *token;
    Node *node1, *node2;
    if (!stackEmpty(context->tokenStack)) {
        stackPush(context->nodeStack, listRemoveLast(context->root->children));
        while (!stackEmpty(context->tokenStack)) {
            token = stackPop(context->tokenStack);
            node1 = stackPop(context->nodeStack);
            node2 = stackPop(context->nodeStack);
            if (node1 == NULL || node2 == NULL) {
                break;
            }
            stackPush(context->nodeStack, nodeBinaryExpressionNew(token->value, node2, node1));
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
    Node *node = context->root;
    while (node != NULL) {
        if (node->children != NULL) {
            for (int i = 0; i < node->children->size; ++i) {
                if (((Node *) node->children->values[i])->type == NT_VarDeclare
                    && strcmp(((VarDeclare *) ((Node *) node->children->values[i])->achiever)->name, name) == 0) {
                    return node->children->values[i];
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
        Node *node = nodeCallVariableNew(identifier->value, var);
        nodeAddChild(context->root, node);
        return;
    }
    if (parseContextPeekNext(context)->type == TT_Colon) {
        parseContextNext(context);
        Node *node = nodeVarDeclareNew(identifier->value);
        nodeAddChild(context->root, node);
        parseContextRunAsRoot(context, node, continueEndWithSemicolon);
        if (listEmpty(node->children)) {
            parseContextTermExpected(context);
        }
    }
}

void parseOperator(ParseContext *context) {
    Node *root = context->root;
    if (root->type == NT_VarDeclare) {
        if (listEmpty(root->children)) {
            parseContextTermExpected(context);
            return;
        }
        stackPush(context->nodeStack, listRemoveLast(root->children));
        Token *token;
        Node *node1, *node2;
        while (!stackEmpty(context->tokenStack) &&
               operatorPriority((token = stackPeek(context->tokenStack))->value) >=
               operatorPriority(parseContextPeekPre(context)->value)) {
            stackPop(context->tokenStack);
            node1 = stackPop(context->nodeStack);
            node2 = stackPop(context->nodeStack);
            if (node1 == NULL || node2 == NULL) {
                break;
            }
            stackPush(context->nodeStack, nodeBinaryExpressionNew(token->value, node2, node1));
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
            Node *node1 = listRemoveLast(root->children), *node2;
            if (node1 == NULL) {
                parseContextTermExpected(context);
                return;
            }
            while (!stackEmpty(context->tokenStack) && (token = stackPop(context->tokenStack))->value[0] != '(') {
                node2 = stackPop(context->nodeStack);
                if (node2 == NULL) {
                    break;
                }
                node1 = nodeBinaryExpressionNew(token->value, node2, node1);
            }
            nodeAddChild(root, node1);
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
        Node *node = nodeNumberLiteralNew(token->value, number, NULL);
        nodeAddChild(context->root, node);
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
        Node *node = nodeNumberLiteralNew(token->value, number, unit);
        nodeAddChild(context->root, node);
        return;
    }
    Node *node = nodeStringLiteralNew(token->value);
    nodeAddChild(context->root, node);
}

void endParse(ParseContext *context) {
    context->ast = NULL;
    context->message = NULL;
    parseContextDel(context);
}
