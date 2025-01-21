#include "inc/lexer/scan_result.h"
#include <malloc.h>
#include <stdio.h>

ScanResult *scanResultNew() {
    ScanResult *result = malloc(sizeof(ScanResult));
    if (!result) {
        return NULL;
    }
    result->tokens = listNew(sizeof(Token *));
    if (!result->tokens) {
        scanResultDel(result);
        return NULL;
    }
    result->message = NULL;
    return result;
}

BOOL scanResultAddToken(ScanResult *result, Token *token) {
    return listAdd(result->tokens, token);
}

void doPrintToken(POINTER token) {
    printf("[%s,%s,offset=%d,row=%d,col=%d]\n",
           tokenTypeAsString(((Token *) token)->type),
           ((Token *) token)->value,
           ((Token *) token)->loc.offset,
           ((Token *) token)->loc.row,
           ((Token *) token)->loc.col
    );
}

void scanResultPrint(ScanResult *result) {
    if (result == NULL) {
        return;
    }
    if (result->message) {
        printf("error message: %s\n", result->message);
    }
    listEach(result->tokens, doPrintToken);
}

void scanResultDel(ScanResult *result) {
    if (result) {
        listEach(result->tokens, (POINTER) tokenDel);
        listDel(result->tokens);
        free(result->message);
        free(result);
    }
}
