#include "inc/ast/parse_result.h"
#include <malloc.h>
#include <stdio.h>

ParseResult *parseResultNew(Ast *ast, char *message) {
    ParseResult *result = malloc(sizeof(ParseResult));
    if (!result) {
        return NULL;
    }
    result->ast = ast;
    result->message = message;
    return result;
}

void parseResultPrint(ParseResult *result) {
    if (result->message) {
        printf("error message: %s\n", result->message);
    }
    if (result->ast != NULL) {
        astPrint(result->ast);
    }
}

void parseResultDel(ParseResult *result) {
    if (result) {
        astDel(result->ast);
        free(result->message);
        free(result);
    }
}
