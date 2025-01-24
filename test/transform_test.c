#include "inc/transform/transform.h"
#include "inc/ast/parser.h"
#include <stdio.h>

int main() {
    ParseConfig *parseConfig = parseConfigNew();
    parseConfig->filePath = "D:\\OpenSource\\less4c\\test\\";
    ParseResult *parseResult = parseToAstByFile(parseConfig, "demo01.less");
    if (parseResult->message == NULL) {
        TransformConfig *config = transformConfigNew();
        Ast *ast = transformToCssAst(config, parseResult->ast);
        astPrint(ast);
        astDel(ast);
        transformConfigDel(config);
    }
    printf("\n\n");
    parseResultPrint(parseResult);
    parseConfigDel(parseConfig);
    parseResultDel(parseResult);
    return 0;
}
