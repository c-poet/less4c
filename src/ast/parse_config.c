#include "inc/ast/parse_config.h"
#include "inc/ast/parse_func.h"
#include "inc/ast/parse_func_private.h"
#include <malloc.h>

ParseConfig *parseConfigNew() {
    ParseConfig *parseConfig = malloc(sizeof(ParseConfig));
    if (!parseConfig) {
        return NULL;
    }
    parseConfigInit(parseConfig);
    return parseConfig;
}

void parseConfigInit(ParseConfig *config) {
    if (!config) {
        return;
    }
    config->filePath = NULL;
    config->fileSuffix = LESS_EXTENSIONS;
    config->startParse = (POINTER) startParse;
    config->parseIdentifier = (POINTER) parseIdentifier;
    config->parseLiteral = (POINTER) parseLiteral;
    config->parseBrace = (POINTER) parseBrace;
    config->parseExpression = (POINTER) parseExpression;
    config->parseKeyword = (POINTER) parseKeyword;
    config->parseImport = (POINTER) parseImport;
    config->endParse = (POINTER) endParse;
    config->readFile = (POINTER) defaultReadFile;
    config->scanToken = (POINTER) defaultScanToken;
}

void parseConfigDel(ParseConfig *config) {
    if (config) {
        free(config);
    }
}
