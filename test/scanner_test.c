#include "inc/lexer/scanner.h"
#include "inc/core/file.h"

int main() {
    String *less = fileReadAll("D:\\OpenSource\\less4c\\test\\demo01.less");
    if (less != NULL) {
        ScanConfig *scanConfig = scanConfigNew();
        ScanResult *result = scanToken(scanConfig, less->chars);
        scanResultPrint(result);
        scanResultDel(result);
        scanConfigDel(scanConfig);
        stringDel(less);
    }
    return 0;
}
