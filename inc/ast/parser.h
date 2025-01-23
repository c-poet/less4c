#ifndef LESS4C_AST_PARSER_H
#define LESS4C_AST_PARSER_H

#include "parse_result.h"
#include "parse_config.h"
#include "inc/lexer/scan_result.h"

/// 解析语法树
/// @param config 解析配置
/// @param tokens Token序列
/// @return 语法树
ParseResult *parseToAst(ParseConfig *config, Token **tokens);

/// 解析语法树
/// @param config 解析配置
/// @param tokens Token列表
/// @return 语法树
ParseResult *parseToAstByList(ParseConfig *config, List *tokens);

/// 解析语法树
/// @param config 解析配置
/// @param result Token描述结果
/// @return 语法树
ParseResult *parseToAstByScanResult(ParseConfig *config, ScanResult *result);

/// 解析语法树
/// @param config 解析配置
/// @param fileName 文件名
/// @return 解析结果
ParseResult *parseToAstByFile(ParseConfig *config, char *fileName);

#endif
