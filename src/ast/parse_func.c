#include "inc/ast/parse_func.h"
#include "inc/ast/node_achiever.h"

void startParse(ParseContext *context) {
    while (parseContextHasNext(context)) {
        Token *token = parseContextNext(context);
        switch (token->type) {
            case TT_Identifier:
                parseIdentifier(context);
                break;
            default:
                break;
        }
    }
}

void parseIdentifier(ParseContext *context) {
    Token *identifier = parseContextPeekPre(context);
    if (parseContextPeekNext(context)->type == TT_Colon) {
        parseContextNext(context);
        if (parseContextPeekNext(context)->type == TT_Literal) {
            VarDeclare *varDeclare = varDeclareNew(identifier->value);
            Node *node = nodeNew(NT_VarDeclare, varDeclare);
            nodeAddChild(context->root, node);
            Node *root = context->root;
            context->root = node;
            parseContextNext(context);
            parseLiteral(context);
            context->root = root;
        }
    }
}

void parseLiteral(ParseContext *context) {
    if (parseContextPeekNext(context)->type != TT_Semicolon) {
        parseContextMessage(context, "Please end with a ';'");
        return;
    }
    Token *token = parseContextPeekPre(context);
    NumberLiteral *literal = numberLiteralNew(token->value);
    Node *node = nodeNew(NT_NumberLiteral, literal);
    nodeAddChild(context->root, node);
}

void endParse(ParseContext *context) {
    context->ast = NULL;
    context->message = NULL;
    parseContextDel(context);
}
