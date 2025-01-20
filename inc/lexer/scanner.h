#ifndef LESS4C_LEXER_SCANNER_H
#define LESS4C_LEXER_SCANNER_H

#include "scan_result.h"

/// 扫描Token序列
/// @param text 文本
/// @return 扫描结果
ScanResult *scanToken(const char *text);

/// 扫描Token序列
/// @param text 文本
/// @param len 文本长度
/// @return 扫描结果
ScanResult *scanTokenByLen(const char *text, int len);

/// 扫描Token序列
/// @param text 文本
/// @param start 开始索引
/// @param end 结束索引（不包含）
/// @return 扫描结果
ScanResult *scanTokenByRange(const char *text, int start, int end);

#endif
