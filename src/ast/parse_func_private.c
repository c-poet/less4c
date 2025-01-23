#include "inc/ast/parse_func_private.h"
#include "inc/ast/node/var_declare.h"
#include "inc/lexer/token_const.h"
#include "inc/core/func.h"
#include "inc/core/file.h"
#include "inc/ast/parser.h"
#include "inc/lexer/scanner.h"
#include <string.h>

Node *findVariable(ParseContext *context, const char *name) {
    List *children;
    Node *node = context->root;
    while (node != NULL) {
        if ((children = nodeGetChildren(node)) != NULL) {
            for (int i = 0; i < children->size; ++i) {
                if (((Node *) children->values[i])->type == NT_VarDeclare
                    && charsEq(((VarDeclare *) children->values[i])->name, name)) {
                    return children->values[i];
                }
            }
        }
        node = node->parent;
    }
    return NULL;
}

BOOL isRulePrelude(ParseContext *context) {
    Token *token;
    int i = context->cur;
    while ((token = context->tokens[i])->type != TT_EOF && token->type != TT_Brace) {
        ++i;
    }
    return token->type == TT_Brace && charsEqChar(token->value, TOKEN_LBRACE);
}

char *doReadFile(char *fileName) {
    String *str = fileReadAll(fileName);
    if (str == NULL) {
        return NULL;
    }
    char *content = str->chars;
    str->chars = NULL;
    stringDel(str);
    return content;
}

char *removeQuote(char *str) {
    int len = (int) strlen(str);
    if (len <= 0) {
        return NULL;
    }
    if (str[0] != TOKEN_QUOTE && str[len - 1] != TOKEN_QUOTE) {
        return NULL;
    }
    String *string = stringNewByLen(len);
    int i = 0;
    if (str[0] == TOKEN_QUOTE) {
        ++i;
    }
    stringAppendCharsRange(string, str, i, len - 1);
    if (str[len - 1] != TOKEN_QUOTE) {
        stringAppendCharsRange(string, str, len - 1, len);
    }
    char *ret = string->chars;
    string->chars = NULL;
    stringDel(string);
    return ret;
}

char *defaultReadFile(ParseConfig *config, char *fileName) {
    if (config->filePath) {
        String *str = stringNew();
        if (str == NULL) {
            return NULL;
        }
        stringAppendChars(str, config->filePath);
        stringAppendChars(str, fileName);
        if (config->fileSuffix && !fileHasExtensions(fileName)) {
            stringAppendChar(str, FILE_EXT_SEPARATOR);
            stringAppendChars(str, config->fileSuffix);
        }
        char *content = doReadFile(str->chars);
        stringDel(str);
        return content;
    }
    return doReadFile(fileName);
}

ScanResult *defaultScanToken(ParseConfig *config, char *content) {
    ScanConfig *scanConfig = scanConfigNew();
    ScanResult *scanResult = scanToken(scanConfig, content);
    scanConfigDel(scanConfig);
    return scanResult;
}

Node *invokeParseGetRootNode(ParseContext *context, char *fileName) {
    ParseResult *parseResult = parseToAstByFile(context->config, fileName);
    if (parseResult == NULL) {
        parseContextTermExpected(context);
        return NULL;
    }
    Node *node = NULL;
    if (parseResult->message != NULL) {
        context->message = parseResult->message;
        parseResult->message = NULL;
    } else {
        node = parseResult->ast->root;
        parseResult->ast->root = NULL;
    }
    parseResultDel(parseResult);
    return node;
}
