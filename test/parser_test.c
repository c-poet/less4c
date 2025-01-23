#include "inc/lexer/scanner.h"
#include "inc/ast/parser.h"

int main() {
    ParseConfig *parseConfig = parseConfigNew();
    parseConfig->filePath = "D:\\OpenSource\\less4c\\test\\";
    ParseResult *parseResult = parseToAstByFile(parseConfig, "demo01.less");
    parseResultPrint(parseResult);
    parseConfigDel(parseConfig);
    parseResultDel(parseResult);
    return 0;
}

