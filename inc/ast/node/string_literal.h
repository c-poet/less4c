#ifndef LESS4C_AST_NODE_STRING_LITERAL_H
#define LESS4C_AST_NODE_STRING_LITERAL_H

#include "node.h"

/// 字符串字面量
typedef struct {
    BASE_NODE

    /// 字符串的值
    char *value;
} StringLiteral;

/// 创建字符串字面量节点
/// @param value 字面量值
/// @return 字符串字面量
StringLiteral *stringLiteralNew(char *value);

/// 打印字符串字面量
/// @param stringLiteral 字符串字面量
/// @param level 层级
void stringLiteralPrint(StringLiteral *stringLiteral, int level);

/// 释放字符串字面量
/// @param stringLiteral 字符串字面量
void stringLiteralDel(StringLiteral *stringLiteral);

#endif
