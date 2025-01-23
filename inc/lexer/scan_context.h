#ifndef LESS4C_LEXER_SCANNER_SC_H
#define LESS4C_LEXER_SCANNER_SC_H

#include "scan_result.h"
#include "scan_config.h"
#include "inc/core/chars_ref.h"

/// 扫描上下文
typedef struct {
    /// 当前索引
    int cur;
    /// 开始索引
    int start;
    /// 结束索引
    int end;
    /// 当前位置信息
    struct {
        /// 当前行
        int row;
        /// 当前列
        int col;
    } loc;
    /// 扫描配置
    ScanConfig *config;
    /// 正在扫描的文本
    const char *text;
    /// 扫描结果返回
    ScanResult *result;
} ScanContext;

/// 实例化扫描上下文
/// @param config 扫描配置
/// @param text 扫描的文本
/// @param start 开始索引
/// @param end 结束索引
/// @return 扫描上下文
ScanContext *scanContextNew(ScanConfig *config, const char *text, int start, int end);

/// 跳过空白符
/// @param context 上下文
/// @return 跳过的空白数
int scanContextSkipSpace(ScanContext *context);

/**
 * 获取上一个字符（索引不移动）
 * @param context  上下文
 * @return  上一个字符
 */
char scanContextPeekPre(ScanContext *context);

/// 获取下一个字符
/// @param context 上下文
/// @return 字符
char scanContextNext(ScanContext *context);

/// 获取下一个字符（索引不移动）
/// @param context 上下文
/// @result 字符
char scanContextPeekNext(ScanContext *context);

/// 获取下一个单词
/// @param context 上下文
/// @return 单词
CharsRef *scanContextNextWord(ScanContext *context);

/// 判断上下文扫描是否结束
/// @param context 上下文
/// @return 是否继续扫描
BOOL scanContextHasNext(ScanContext *context);

/// 填充Token信息
/// @param context 上下文
/// @param token Token
void scanContextFillToken(ScanContext *context, Token *token);

/// 填充Token信息并添加到结果
/// @param context 上下文
/// @param token Token
void scanContextAddToken(ScanContext *context, Token *token);

/// 设置错误信息
/// @param context 上下文
/// @param message 错误信息
void scanContextError(ScanContext *context, char *message);

/// 释放扫描上下文
/// @param context 扫描上下文
void scanContextDel(ScanContext *context);

#endif
