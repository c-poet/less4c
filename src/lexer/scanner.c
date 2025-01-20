#include "inc/lexer/scanner.h"
#include "inc/lexer/scan_context.h"
#include "inc/lexer/scan_func.h"
#include <string.h>

ScanResult *scanToken(const char *text) {
    return scanTokenByLen(text, (int) strlen(text));
}

ScanResult *scanTokenByLen(const char *text, int len) {
    return scanTokenByRange(text, 0, len);
}

ScanResult *scanTokenByRange(const char *text, int start, int end) {
    if (start >= end || text == NULL) {
        return NULL;
    }
    ScanContext *context = scanContextNew(text, start, end);
    if (!context) {
        return NULL;
    }
    startScan(context);
    ScanResult *result = context->result;
    endScan(context);
    return result;
}
