#ifndef LESS4C_LEXER_SCANNER_SR_H
#define LESS4C_LEXER_SCANNER_SR_H

#include "token.h"
#include "inc/core/list.h"

/// 扫描结果
typedef struct {
    /// Token序列
    List *tokens;
    /// 错误信息（未发生错误时返回null）
    char *message;
} ScanResult;

/// 创建扫描结果
/// @return 扫描结果
ScanResult *scanResultNew();

/// 添加token到扫描结果中
/// @param result 结果
/// @param token 需要添加的token
BOOL scanResultAddToken(ScanResult *result, Token *token);

/// 打印扫描结果
/// @param result 扫描结果
void scanResultPrint(ScanResult *result);

/// 释放结果
/// @param result 结果
void scanResultDel(ScanResult *result);

#endif
