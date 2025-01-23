#ifndef LESS4C_LEXER_SCAN_CONFIG_H
#define LESS4C_LEXER_SCAN_CONFIG_H

#include "inc/core/global.h"

/// 扫描处理方法
typedef void (*ScanHandler)(POINTER);

/// 扫描配置
typedef struct {
    /// 开始扫描
    ScanHandler startScan;
    /// 扫描@符号
    ScanHandler scanAt;
    /// 扫描"{" or "}"
    ScanHandler scanBrace;
    /// 扫描"(" or ")"
    ScanHandler scanBracket;
    /// 扫描":"
    ScanHandler scanColon;
    /// 扫描逻辑运算符
    ScanHandler scanLogic;
    /// 扫描运算符
    ScanHandler scanOperator;
    /// 扫描 "/"
    ScanHandler scanSlash;
    /// 扫描 ";"
    ScanHandler scanSemicolon;
    /// 扫描字面量
    ScanHandler scanLiteral;
    /// 结束扫描
    ScanHandler endScan;
} ScanConfig;

/// 创建扫描配置
/// @return 扫描配置
ScanConfig *scanConfigNew();

/// 初始化扫描配置
/// @param scanConfig 扫描配置
void scanConfigInit(ScanConfig *scanConfig);

/// 释放扫描配置
/// @param scanConfig 扫描配置
void scanConfigDel(ScanConfig *scanConfig);

#endif
