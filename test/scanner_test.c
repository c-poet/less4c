#include "inc/lexer/scanner.h"
#include "inc/core/file.h"

int main() {
    String *less = fileReadAll("D:\\OpenSource\\less4c\\test\\demo01.less");
    if (less != NULL) {
        ScanResult *result = scanToken(less->chars);
        scanResultPrint(result);
        scanResultDel(result);
        stringDel(less);
    }
    return 0;
}
