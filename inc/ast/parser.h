#ifndef LESS4C_AST_PARSER_H
#define LESS4C_AST_PARSER_H

#include "parse_result.h"
#include "inc/lexer/scan_result.h"

/// 解析语法树
/// @param tokens Token序列
/// @return 语法树
ParseResult *parseToAst(Token **tokens);

/// 解析语法树
/// @param tokens Token列表
/// @return 语法树
ParseResult *parseToAstByList(List *tokens);

/// 解析语法树
/// @param result Token描述结果
/// @return 语法树
ParseResult *parseToAstByScanResult(ScanResult *result);

#endif
