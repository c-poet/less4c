#include "inc/lexer/scan_context.h"
#include "inc/core/str.h"
#include <malloc.h>

ScanContext *scanContextNew(const char *text, int start, int end) {
    ScanContext *context = malloc(sizeof(ScanContext));
    if (!context) {
        return NULL;
    }
    context->cur = start;
    context->start = start;
    context->loc.row = 1;
    context->loc.col = 0;
    context->end = end;
    context->text = text;
    context->result = scanResultNew();
    if (!context->result) {
        scanContextDel(context);
        return NULL;
    }
    return context;
}

int scanContextSkipSpace(ScanContext *context) {
    char c;
    int i = context->cur;
    while (scanContextHasNext(context)) {
        c = scanContextPeekNext(context);
        if (c != ' ' && c != '\n' && c != '\t') {
            break;
        }
        scanContextNext(context);
    }
    return context->cur - i;
}

char scanContextPeekPre(ScanContext *context) {
    return context->text[context->cur - 1];
}

char scanContextNext(ScanContext *context) {
    char c = context->text[context->cur++];
    if (c == '\n') {
        ++context->loc.row;
        context->loc.col = 0;
    } else {
        ++context->loc.col;
    }
    return c;
}

char scanContextPeekNext(ScanContext *context) {
    return context->text[context->cur];
}

BOOL scanContextHasNext(ScanContext *context) {
    return context->cur < context->end && !context->result->message;
}

void scanContextFillToken(ScanContext *context, Token *token) {
    token->loc.offset = context->cur;
    token->loc.row = context->loc.row;
    token->loc.col = context->loc.col;
}

void scanContextAddToken(ScanContext *context, Token *token) {
    if (!token) {
        scanContextError(context, "The added token is NULL");
    } else {
        scanContextFillToken(context, token);
        scanResultAddToken(context->result, token);
    }
}

CharsRef *scanContextNextWord(ScanContext *context) {
    scanContextSkipSpace(context);
    if (!scanContextHasNext(context)) {
        return NULL;
    }
    char c;
    int i = context->cur;
    while (scanContextHasNext(context)) {
        c = scanContextPeekNext(context);
        if (!(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c == '-')) {
            break;
        }
        scanContextNext(context);
    }
    if (context->cur <= i) {
        return NULL;
    }
    return charsRefNew(context->text, i, context->cur);
}

void scanContextError(ScanContext *context, char *message) {
    String *string = stringNew();
    if (string) {
        stringAppendChars(string, message);
        stringAppendChars(string, " row: ");
        stringAppendInt(string, context->loc.row);
        stringAppendChars(string, " col: ");
        stringAppendInt(string, context->loc.col);
        context->result->message = string->chars;
        string->chars = NULL;
        free(string);
    }
}

void scanContextDel(ScanContext *context) {
    if (context) {
        scanResultDel(context->result);
        free(context);
    }
}
