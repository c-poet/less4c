#ifndef LESS4C_AST_PARSE_FUNC_H
#define LESS4C_AST_PARSE_FUNC_H

#include "parse_context.h"

/// 开始解析
/// @param context 上下文
void startParse(ParseContext *context);

/// 解析Identifier
/// @param context 上下文
void parseIdentifier(ParseContext *context);

/// 解析运算符
/// @param context 上下文
void parseOperator(ParseContext *context);

/// 解析花括号
/// @param context 上下文
void parseBrace(ParseContext *context);

/// 解析括号
/// @param context 上下文
void parseBracket(ParseContext *context);

/// 解析字面量
/// @param context 上下文
void parseLiteral(ParseContext *context);

/// 结束解析
/// @param context 上下文
void endParse(ParseContext *context);

#endif
