#ifndef LESS4C_AST_NODE_STRING_LITERAL_H
#define LESS4C_AST_NODE_STRING_LITERAL_H

#include "node.h"

/// 字符串字面量
typedef struct {
    BASE_NODE

    /// 字符串的值
    const char *value;
} StringLiteral;

/// 创建字符串字面量节点
/// @param val 字面量值
/// @return 字符串字面量
StringLiteral *stringLiteralNew(const char *val);

void stringLiteralPrint(StringLiteral *stringLiteral, int level);

void stringLiteralDel(StringLiteral *stringLiteral);

#endif
