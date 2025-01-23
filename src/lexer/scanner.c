#include "inc/lexer/scanner.h"
#include "inc/lexer/scan_context.h"
#include <string.h>

ScanResult *scanToken(ScanConfig *config, const char *text) {
    return scanTokenByLen(config, text, (int) strlen(text));
}

ScanResult *scanTokenByLen(ScanConfig *config, const char *text, int len) {
    return scanTokenByRange(config, text, 0, len);
}

ScanResult *scanTokenByRange(ScanConfig *config, const char *text, int start, int end) {
    if (start >= end || text == NULL) {
        return NULL;
    }
    ScanContext *context = scanContextNew(config, text, start, end);
    if (!context) {
        return NULL;
    }
    config->startScan(context);
    ScanResult *result = context->result;
    config->endScan(context);
    return result;
}
