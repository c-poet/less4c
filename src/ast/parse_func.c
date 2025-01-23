#include "inc/ast/parse_func.h"
#include "inc/ast/parse_func_private.h"
#include "inc/core/style.h"
#include "inc/core/func.h"
#include "inc/ast/priority.h"
#include "inc/core/stack.h"
#include "inc/lexer/token_const.h"
#include "inc/ast/node/number_literal.h"
#include "inc/ast/node/string_literal.h"
#include "inc/ast/node/var_declare.h"
#include "inc/ast/node/call_variable.h"
#include "inc/ast/node/binary_expression.h"
#include "inc/ast/node/rule.h"
#include "inc/ast/node/block.h"
#include "inc/ast/node/selectors.h"
#include "inc/ast/node/selector.h"
#include "inc/ast/node/value.h"
#include "inc/ast/node/declaration.h"
#include "inc/ast/node/id_selector.h"
#include "inc/ast/node/type_selector.h"
#include "inc/ast/node/class_selector.h"
#include "inc/ast/node/pseudo_class_selector.h"
#include "inc/ast/node/pseudo_element_selector.h"
#include <string.h>

void invokeParse(ParseContext *context) {
    while (parseContextHasNext(context)) {
        Token *token = parseContextNext(context);
        switch (token->type) {
            case TT_Identifier:
                parseIdentifier(context);
                break;
            case TT_Literal:
            case TT_Operator:
            case TT_Colon:
                parseLiteral(context);
                break;
            case TT_Brace:
                if (context->root->type == NT_Block && charsEqChar(token->value, TOKEN_RBRACE)) {
                    return;
                }
                parseBrace(context);
                break;
            default:
                parseContextTermExpected(context);
                break;
        }
    }
}

void startParse(ParseContext *context) {
    invokeParse(context);
}

void parseIdentifier(ParseContext *context) {
    Token *identifier = parseContextPeekPre(context);
    if (context->root->type == NT_Value) {
        Node *var = findVariable(context, identifier->value);
        if (var == NULL) {
            parseContextMessage(context, "Cannot find variable");
            return;
        }
        CallVariable *callVariable = callVariableNew(identifier->value, var);
        parseContextRootAddChild(context, (POINTER) callVariable);
        return;
    }
    if (parseContextHasNext(context) && parseContextPeekNext(context)->type == TT_Colon) {
        parseContextNext(context);
        Value *value = valueNew();
        VarDeclare *varDeclare = varDeclareNew(identifier->value, (POINTER) value);
        parseContextRootAddChild(context, (POINTER) varDeclare);
        parseContextRunAsRoot(context, (POINTER) value, parseExpression);
        if (listEmpty(value->children)) {
            parseContextTermExpected(context);
        }
        return;
    }
    parseContextTermExpected(context);
}

void parseLiteral(ParseContext *context) {
    Token *token = parseContextPeekPre(context);
    double number = 0;
    if (charsToDouble(token->value, &number)) {
        NumberLiteral *numberLiteral = numberLiteralNew(token->value, number, NULL);
        parseContextRootAddChild(context, (POINTER) numberLiteral);
        return;
    }
    const char *unit = NULL;
    int l2, l1 = (int) strlen(token->value);
    for (int i = 0; i < 16; ++i) {
        l2 = (int) strlen(STYLE_UNITS[i]);
        if (l1 > l2 && charsEq(token->value + l1 - l2, STYLE_UNITS[i])) {
            unit = STYLE_UNITS[i];
            break;
        }
    }
    if (unit != NULL && charsToDoubleByRange(token->value, 0, l1 - l2, &number)) {
        NumberLiteral *numberLiteral = numberLiteralNew(token->value, number, unit);
        parseContextRootAddChild(context, (POINTER) numberLiteral);
        return;
    }
    if (parseContextHasNext(context) && charsEqChar(parseContextPeekNext(context)->value, TOKEN_COLON) &&
        !isRulePrelude(context)) {
        if (context->root->type != NT_Block) {
            parseContextTermExpected(context);
            return;
        }
        parseContextNext(context);
        Value *value = valueNew();
        Declaration *declaration = declarationNew(token->value, (POINTER) value);
        parseContextRootAddChild(context, (POINTER) declaration);
        parseContextRunAsRoot(context, (POINTER) value, parseExpression);
    } else {
        StringLiteral *stringLiteral = stringLiteralNew(token->value);
        parseContextRootAddChild(context, (POINTER) stringLiteral);
    }
}

Selectors *createSelectors(ParseContext *context) {
    List *children = nodeGetChildren(context->root);
    if (children == NULL) {
        return NULL;
    }
    int index = children->size - 1;
    while (index >= 0 && ((Node *) children->values[index])->type == NT_StringLiteral) {
        --index;
    }
    if (index == children->size - 1) {
        return NULL;
    }
    ++index;
    int colonCount = 0;
    Selectors *selectors = selectorsNew();
    Selector *selector = selectorNew();
    while (index < children->size) {
        StringLiteral *literal = (StringLiteral *) listRemoveByIndex(children, index);
        if (charsEqChar(literal->value, TOKEN_COMMA)) {
            if (!listEmpty(selector->children)) {
                nodeAddChild((POINTER) selectors, (POINTER) selector);
                selector = selectorNew();
            }
        } else if (literal->value[0] == TOKEN_WELL) {
            IdSelector *idSelector = idSelectorNew(literal->value + 1);
            nodeAddChild((POINTER) selector, (POINTER) idSelector);
        } else if (literal->value[0] == TOKEN_DOT) {
            ClassSelector *classSelector = classSelectorNew(literal->value + 1);
            nodeAddChild((POINTER) selector, (POINTER) classSelector);
        } else if (charsEqChar(literal->value, TOKEN_COLON)) {
            ++colonCount;
        } else if (colonCount == 1) {
            PseudoClassSelector *pseudoClassSelector = pseudoClassSelectorNew(literal->value);
            nodeAddChild((POINTER) selector, (POINTER) pseudoClassSelector);
            colonCount = 0;
        } else if (colonCount > 1) {
            PseudoElementSelector *pseudoElementSelector = pseudoElementSelectorNew(literal->value);
            nodeAddChild((POINTER) selector, (POINTER) pseudoElementSelector);
            colonCount = 0;
        } else {
            TypeSelector *typeSelector = typeSelectorNew(literal->value);
            nodeAddChild((POINTER) selector, (POINTER) typeSelector);
        }
    }
    nodeAddChild((POINTER) selectors, (POINTER) selector);
    return selectors;
}

void parseBrace(ParseContext *context) {
    if (charsEqChar(parseContextPeekPre(context)->value, TOKEN_LBRACE)) {
        Selectors *selectors = createSelectors(context);
        if (selectors == NULL) {
            parseContextTermExpected(context);
            return;
        }
        Block *block = blockNew();
        Rule *rule = ruleNew((POINTER) selectors, (POINTER) block);
        parseContextRootAddChild(context, (POINTER) rule);
        parseContextRunAsRoot(context, (POINTER) block, invokeParse);
        if (parseContextPeekPre(context)->type != TT_Brace &&
            charsEqChar(parseContextPeekPre(context)->value, TOKEN_RBRACE)) {
            parseContextTermExpected(context);
        }
        return;
    }
    parseContextTermExpected(context);
}

void parseExpressionOperator(ParseContext *context, Stack *opStack, Stack *nodeStack, Token *token) {
    Node *right = listRemoveLast(nodeGetChildren(context->root));
    if (right == NULL) {
        parseContextTermExpected(context);
        return;
    }
    Node *left;
    while (!stackEmpty(opStack) &&
           operatorPriority(((Token *) stackPeek(opStack))->value) >= operatorPriority(token->value)) {
        left = stackPop(nodeStack);
        if (left == NULL) {
            parseContextTermExpected(context);
            break;
        }
        right = (POINTER) binaryExpressionNew(((Token *) stackPop(opStack))->value, left, right);
    }
    stackPush(nodeStack, right);
    stackPush(opStack, token);
}

void parseExpressionBracket(ParseContext *context, Stack *opStack, Stack *nodeStack, Token *token) {
    if (charsEqChar(token->value, TOKEN_LBRACKET)) {
        stackPush(opStack, token);
    } else {
        Node *right = listRemoveLast(nodeGetChildren(context->root)), *left;
        if (right == NULL) {
            parseContextTermExpected(context);
            return;
        }
        while (!stackEmpty(opStack) && !charsEqChar((token = stackPop(opStack))->value, TOKEN_LBRACKET) &&
               (left = stackPop(nodeStack)) != NULL) {
            right = (POINTER) binaryExpressionNew(token->value, left, right);
        }
        parseContextRootAddChild(context, right);
        if (!charsEqChar(token->value, TOKEN_LBRACKET)) {
            parseContextTermExpected(context);
        }
    }
}

void parseExpressionEnd(ParseContext *context, Stack *opStack, Stack *nodeStack) {
    Node *right = listRemoveLast(nodeGetChildren(context->root));
    if (right == NULL) {
        parseContextTermExpected(context);
    } else {
        Node *left;
        Token *token;
        while (!stackEmpty(opStack) && (left = stackPop(nodeStack)) != NULL) {
            token = stackPop(opStack);
            right = (POINTER) binaryExpressionNew(token->value, left, right);
        }
        parseContextRootAddChild(context, right);
    }
    if (!stackEmpty(opStack) || !stackEmpty(nodeStack)) {
        parseContextTermExpected(context);
    }
    while (!stackEmpty(nodeStack)) {
        nodeDel(stackPop(nodeStack));
    }
}

void parseExpression(ParseContext *context) {
    List *children = nodeGetChildren(context->root);
    if (children == NULL) {
        parseContextTermExpected(context);
        return;
    }
    Token *token = NULL;
    Stack *opStack = stackNew(sizeof(Token *)), *nodeStack = stackNew(sizeof(Node *));
    while (parseContextHasNext(context) && (token = parseContextNext(context))->type != TT_Semicolon) {
        switch (token->type) {
            case TT_Literal:
                parseLiteral(context);
                break;
            case TT_Identifier:
                parseIdentifier(context);
                break;
            case TT_Logic:
            case TT_Operator:
                parseExpressionOperator(context, opStack, nodeStack, token);
                break;
            case TT_Bracket:
                parseExpressionBracket(context, opStack, nodeStack, token);
                break;
            default:
                parseContextTermExpected(context);
                break;
        }
    }
    parseExpressionEnd(context, opStack, nodeStack);
    stackDel(opStack);
    stackDel(nodeStack);
}

void endParse(ParseContext *context) {
    context->ast = NULL;
    context->message = NULL;
    parseContextDel(context);
}
