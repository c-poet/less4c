#ifndef LESS4C_AST_PARSE_FUNC_H
#define LESS4C_AST_PARSE_FUNC_H

#include "parse_context.h"

/// 开始解析
/// @param context 上下文
void startParse(ParseContext *context);

/// 解析Identifier
/// @param context 上下文
void parseIdentifier(ParseContext *context);

/// 解析字面量
/// @param context 上下文
void parseLiteral(ParseContext *context);

/// 解析块
/// @param context 上下文
void parseBrace(ParseContext *context);

/// 解析表达式
/// @param context 上下文
void parseExpression(ParseContext *context);

/// 解析关键字
/// @param context 上下文
void parseKeyword(ParseContext *context);

/// 解析导入
/// @param context 上下文
void parseImport(ParseContext *context);

/// 结束解析
/// @param context 上下文
void endParse(ParseContext *context);

#endif
