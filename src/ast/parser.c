#include "inc/ast/parser.h"
#include "inc/ast/parse_context.h"
#include <malloc.h>

ParseResult *parseToAst(ParseConfig *config, Token **tokens) {
    ParseContext *context = parseContextNew(config, tokens);
    if (!context) {
        return NULL;
    }
    config->startParse(context);
    ParseResult *result = parseResultNew(context->ast, context->message);
    config->endParse(context);
    return result;
}

ParseResult *parseToAstByList(ParseConfig *config, List *tokens) {
    return parseToAst(config, (Token **) tokens->values);
}

ParseResult *parseToAstByScanResult(ParseConfig *config, ScanResult *result) {
    return parseToAstByList(config, result->tokens);
}

ParseResult *parseToAstByFile(ParseConfig *config, char *fileName) {
    char *content = config->readFile(config, fileName);
    if (content == NULL) {
        return NULL;
    }
    ScanResult *scanResult = config->scanToken(config, content);
    free(content);
    if (scanResult == NULL) {
        return NULL;
    }
    ParseResult *parseResult;
    if (scanResult->message != NULL) {
        parseResult = parseResultNew(NULL, scanResult->message);
        scanResult->message = NULL;
    } else {
        parseResult = parseToAstByScanResult(config, scanResult);
    }
    scanResultDel(scanResult);
    return parseResult;
}
