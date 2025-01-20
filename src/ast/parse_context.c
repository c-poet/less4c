#include "inc/ast/parse_context.h"
#include "inc/core/str.h"
#include <malloc.h>

ParseContext *parseContextNew(Token **tokens) {
    Ast *ast = astNew();
    if (!ast) {
        return NULL;
    }
    ParseContext *context = malloc(sizeof(ParseContext));
    if (!context) {
        astDel(ast);
        return NULL;
    }
    context->cur = 0;
    context->ast = ast;
    context->root = ast->root;
    context->tokens = tokens;
    context->message = NULL;
    return context;
}

BOOL parseContextHasNext(ParseContext *context) {
    return context->tokens[context->cur]->type != TT_EOF && context->message == NULL;
}

Token *parseContextPeekPre(ParseContext *context) {
    return context->tokens[context->cur - 1];
}

Token *parseContextNext(ParseContext *context) {
    return context->tokens[context->cur]->type != TT_EOF ? context->tokens[context->cur++] : NULL;
}

Token *parseContextPeekNext(ParseContext *context) {
    return context->tokens[context->cur];
}

void parseContextMessage(ParseContext *context, char *message) {
    String *str = stringNew();
    if (str) {
        Token *token = parseContextPeekNext(context);
        stringAppendChars(str, message);
        stringAppendChars(str, " row: ");
        stringAppendInt(str, token->loc.row);
        stringAppendChars(str, " col: ");
        stringAppendInt(str, token->loc.col);
        context->message = str->chars;
        str->chars = NULL;
        free(str);
    }
}

void parseContextDel(ParseContext *context) {
    if (context) {
        free(context->message);
        astDel(context->ast);
        free(context);
    }
}
