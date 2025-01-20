#include "inc/ast/parser.h"
#include "inc/ast/parse_func.h"

ParseResult *parseToAst(Token **tokens) {
    ParseContext *context = parseContextNew(tokens);
    if (!context) {
        return NULL;
    }
    startParse(context);
    ParseResult *result = parseResultNew(context->ast, context->message);
    endParse(context);
    return result;
}

ParseResult *parseToAstByList(List *tokens) {
    return parseToAst((Token **) tokens->values);
}

ParseResult *parseToAstByScanResult(ScanResult *result) {
    return parseToAstByList(result->tokens);
}
