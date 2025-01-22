#ifndef LESS4C_AST_NODE_NUMBER_LITERAL_H
#define LESS4C_AST_NODE_NUMBER_LITERAL_H

#include "node.h"

/// 数字字面量
typedef struct {
    BASE_NODE

    /// 数字值
    const char *value;
    /// 数值
    double number;
    /// 单位
    const char *unit;
} NumberLiteral;

/// 创建数字字面量节点
/// @param val 字面量值
/// @param number 数值
/// @param unit 单位
/// @return 数字字面量
NumberLiteral *numberLiteralNew(const char *val, double number, const char *unit);

void numberLiteralPrint(NumberLiteral *numberLiteral, int level);

void numberLiteralDel(NumberLiteral *numberLiteral);

#endif
