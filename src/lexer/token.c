#include "inc/lexer/token.h"
#include <malloc.h>

Token *tokenNew(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    if (!token) {
        return NULL;
    }
    token->type = type;
    token->loc.offset = 0;
    token->loc.row = 0;
    token->loc.col = 0;
    token->value = value;
    return token;
}

Token *tokenNewByRange(TokenType type, const char *text, int start, int end) {
    int len = end - start;
    char *chars = malloc(sizeof(char) * (len + 1));
    if (!chars) {
        return NULL;
    }
    int i = 0;
    while (i < len) {
        chars[i] = text[start + i];
        ++i;
    }
    chars[len] = STR_EOF;
    Token *token = tokenNew(type, chars);
    if (!token) {
        free(chars);
    }
    return token;
}

Token *tokenNewByChar(TokenType type, char c) {
    char *chars = malloc(sizeof(char) * 2);
    if (!chars) {
        return NULL;
    }
    chars[0] = c;
    chars[1] = STR_EOF;
    Token *token = tokenNew(type, chars);
    if (!token) {
        free(chars);
    }
    return token;
}

Token *tokenNewByCharsRef(TokenType type, CharsRef *charsRef) {
    char *chars = charsRefToChars(charsRef);
    if (!chars) {
        return NULL;
    }
    Token *token = tokenNew(type, chars);
    if (!token) {
        free(chars);
    }
    return token;
}

void tokenDel(Token *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}

char *tokenTypeAsString(TokenType type) {
    switch (type) {
        case TT_Identifier:
            return "Identifier";
        case TT_Operator:
            return "Operator";
        case TT_Logic:
            return "Logic";
        case TT_Keyword:
            return "Keyword";
        case TT_Literal:
            return "Literal";
        case TT_Brace:
            return "Brace";
        case TT_Bracket:
            return "Bracket";
        case TT_Semicolon:
            return "Semicolon";
        case TT_Colon:
            return "Colon";
        case TT_EOF:
            return "EOF";
        default:
            return "";
    }
}
