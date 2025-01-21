#include "inc/lexer/scanner.h"
#include "inc/ast/parser.h"
#include "inc/core/file.h"

#include <stdio.h>

int main() {
    String *less = fileReadAll("D:\\OpenSource\\less4c\\test\\demo01.less");
    if (less != NULL) {
        ScanResult *result = scanToken(less->chars);
        if (result != NULL) {
            ParseResult *parseResult = parseToAstByScanResult(result);
            parseResultPrint(parseResult);
            parseResultDel(parseResult);
        }
        scanResultDel(result);
        stringDel(less);
    }
    return 0;
}

