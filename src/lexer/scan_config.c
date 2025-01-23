#include "inc/lexer/scan_config.h"
#include "inc/lexer/scan_func.h"
#include <malloc.h>

/// 创建扫描配置
/// @return 扫描配置
ScanConfig *scanConfigNew() {
    ScanConfig *scanConfig = malloc(sizeof(ScanConfig));
    if (!scanConfig) {
        return NULL;
    }
    scanConfigInit(scanConfig);
    return scanConfig;
}

void scanConfigInit(ScanConfig *scanConfig) {
    if (!scanConfig) {
        return;
    }
    scanConfig->startScan = (POINTER) startScan;
    scanConfig->scanAt = (POINTER) scanAt;
    scanConfig->scanBrace = (POINTER) scanBrace;
    scanConfig->scanBracket = (POINTER) scanBracket;
    scanConfig->scanColon = (POINTER) scanColon;
    scanConfig->scanLogic = (POINTER) scanLogic;
    scanConfig->scanOperator = (POINTER) scanOperator;
    scanConfig->scanSlash = (POINTER) scanSlash;
    scanConfig->scanSemicolon = (POINTER) scanSemicolon;
    scanConfig->scanLiteral = (POINTER) scanLiteral;
    scanConfig->endScan = (POINTER) endScan;
}

void scanConfigDel(ScanConfig *scanConfig) {
    if (scanConfig) {
        free(scanConfig);
    }
}
