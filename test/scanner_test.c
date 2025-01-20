#include "inc/lexer/scanner.h"
#include "inc/core/file.h"

int main() {
    String *less = fileReadAll("D:\\OpenSource\\c-less-to-css\\test\\demo01.less");
    if (less != NULL) {
        ScanResult *result = scanToken(less->chars);
        scanResultPrint(result);
        scanResultDel(result);
        stringDel(less);
    }
    return 0;
}
