#ifndef C_C2L_PARSE_RESULT_H
#define C_C2L_PARSE_RESULT_H

#include "ast.h"

/// 解析结果
typedef struct {
    /// 语法树
    Ast *ast;
    /// 返回信息
    char *message;
} ParseResult;

/// 实例化解析结果
/// @return 解析结果
ParseResult *parseResultNew(Ast *ast, char *message);

/// 打印解析结果
/// @param result 解析结果
void parseResultPrint(ParseResult *result);

/// 释放解析结果
/// @param result 解释结果
void parseResultDel(ParseResult *result);

#endif
