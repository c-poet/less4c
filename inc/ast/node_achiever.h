#ifndef LESS4C_AST_NODE_ACHIEVER_H
#define LESS4C_AST_NODE_ACHIEVER_H

#include "inc/core/global.h"

/// 变量声明
typedef struct {
    /// 变量名
    char *name;
} VarDeclare;

/// 数字字面量
typedef struct {
    /// 数字值
    char *value;
    /// 单位
    char *unit;
} NumberLiteral;

/// 字符串字面量
typedef struct {
    /// 字符串的值
    char *value;
} StringLiteral;

/// 实例变量申请
/// @param name 变量名
/// @return 变量申明
VarDeclare *varDeclareNew(char *name);

NumberLiteral *numberLiteralNew(char *val);

#endif
