#ifndef LESS4C_LEXER_SCANNER_FUNC_H
#define LESS4C_LEXER_SCANNER_FUNC_H

#include "scan_context.h"

/// 开始扫描
/// @param context 上下文
void startScan(ScanContext *context);

/// 扫描@符号
/// @param context 上下文
void scanAt(ScanContext *context);

/// 扫描"{" or "}"
/// @param context 上下文
void scanBrace(ScanContext *context);

/// 扫描"(" or ")"
/// @param context 上下文
void scanBracket(ScanContext *context);

/// 扫描":"
/// @param context 上下文
void scanColon(ScanContext *context);

/// 扫描逻辑运算符
/// @param context 上下文
void scanLogic(ScanContext  *context);

/// 扫描运算符
/// @param context 上下文
void scanOperator(ScanContext *context);

/// 扫描 "/"
/// @param context 上下文
void scanSlash(ScanContext *context);

/// 扫描 ";"
/// @param context 上下文
void scanSemicolon(ScanContext *context);

/// 扫描字面量
/// @param context 上下文
void scanLiteral(ScanContext *context);

/// 结束扫描
/// @param context 上下文
void endScan(ScanContext *context);

#endif
