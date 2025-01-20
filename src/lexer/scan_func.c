#include "inc/lexer/scan_func.h"
#include "inc/lexer/token_const.h"

void startScan(ScanContext *context) {
    while (scanContextSkipSpace(context) >= 0 && scanContextHasNext(context)) {
        switch (scanContextNext(context)) {
            case TOKEN_AT:
                scanAt(context);
                break;
            case TOKEN_LBRACE:
            case TOKEN_RBRACE:
                scanBrace(context);
                break;
            case TOKEN_LBRACKET:
            case TOKEN_RBRACKET:
                scanBracket(context);
                break;
            case TOKEN_COLON:
                scanColon(context);
                break;
            case TOKEN_GT:
            case TOKEN_LT:
            case TOKEN_EQ:
                scanLogin(context);
                break;
            case '+':
            case '-':
            case '*':
                scanOperator(context);
                break;
            case TOKEN_SLASH:
                scanSlash(context);
                break;
            case TOKEN_SEMICOLON:
                scanSemicolon(context);
                break;
            default:
                scanLiteral(context);
        }

    }
}

void scanAt(ScanContext *context) {
    CharsRef *word = scanContextNextWord(context);
    charsRefMoveStartIndex(word, -1);
    if (charsRefEqualsChars(word, TOKEN_IMPORT)) {
        Token *token = tokenNewByCharsRef(TT_Keyword, word);
        scanContextAddToken(context, token);
    } else {
        Token *token = tokenNewByCharsRef(TT_Identifier, word);
        scanContextAddToken(context, token);
    }
    charsRefDel(word);
}

void scanBrace(ScanContext *context) {
    Token *token = tokenNewByChar(TT_Brace, scanContextPeekPre(context));
    scanContextAddToken(context, token);
}

void scanBracket(ScanContext *context) {
    Token *token = tokenNewByChar(TT_Bracket, scanContextPeekPre(context));
    scanContextAddToken(context, token);
}

void scanColon(ScanContext *context) {
    if (scanContextHasNext(context) && scanContextPeekNext(context) != TOKEN_COLON) {
        Token *token = tokenNewByChar(TT_Colon, scanContextPeekPre(context));
        scanContextAddToken(context, token);
        return;
    }
}


void scanLogin(ScanContext *context) {
    if ((scanContextPeekPre(context) == TOKEN_GT || scanContextPeekPre(context) == TOKEN_LT) &&
        scanContextHasNext(context) && scanContextPeekNext(context) == TOKEN_EQ) {
        scanContextNext(context);
        Token *token = tokenNewByRange(TT_Logic, context->text, context->cur - 2, context->cur);
        scanContextAddToken(context, token);
        return;
    }
    Token *token = tokenNewByChar(TT_Logic, scanContextPeekPre(context));
    scanContextAddToken(context, token);
}

void scanOperator(ScanContext *context) {
    Token *token = tokenNewByChar(TT_Operator, scanContextPeekPre(context));
    scanContextAddToken(context, token);
}

void scanSlash(ScanContext *context) {
    // 单行注释
    if (scanContextPeekNext(context) == TOKEN_SLASH) {
        char c;
        do {
            c = scanContextNext(context);
        } while (scanContextHasNext(context) && c != TOKEN_LF);
        return;
    }
    // 多行注释
    if (scanContextPeekNext(context) == TOKEN_ASTERISK) {
        scanContextNext(context);
        char c;
        do {
            c = scanContextNext(context);
        } while (scanContextHasNext(context) && (c != TOKEN_ASTERISK || scanContextPeekNext(context) != TOKEN_SLASH));
        if (c == TOKEN_ASTERISK && scanContextHasNext(context) && scanContextPeekNext(context) == TOKEN_SLASH) {
            scanContextNext(context);
        } else {
            scanContextError(context, "Multi line comments not closed");
        }
        return;
    }
    scanOperator(context);
}

void scanSemicolon(ScanContext *context) {
    Token *token = tokenNewByChar(TT_Semicolon, scanContextPeekPre(context));
    scanContextAddToken(context, token);
}

void scanLiteral(ScanContext *context) {
    char c;
    int i = context->cur - 1;
    while (scanContextHasNext(context)) {
        c = scanContextPeekNext(context);
        if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == TOKEN_UNDERLINE ||
              c == TOKEN_AT || c == TOKEN_ROD)) {
            break;
        }
        scanContextNext(context);
    }
    Token *token = tokenNewByRange(TT_Literal, context->text, i, context->cur);
    scanContextAddToken(context, token);
}

void endScan(ScanContext *context) {
    Token *token = tokenNewByChar(TT_EOF, STR_EOF);
    scanContextAddToken(context, token);
    context->result = NULL;
    scanContextDel(context);
}
