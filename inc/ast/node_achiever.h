#ifndef LESS4C_AST_NODE_ACHIEVER_H
#define LESS4C_AST_NODE_ACHIEVER_H

#include "inc/core/global.h"
#include "node.h"

/// 变量声明
typedef struct {
    /// 变量名
    const char *name;
} VarDeclare;

/// 调用变量
typedef struct {
    /// 变量名
    const char *name;
    /// 变量所在节点
    const Node *var;
} CallVariable;

/// 数字字面量
typedef struct {
    /// 数字值
    const char *value;
    /// 数值
    double number;
    /// 单位
    const char *unit;
} NumberLiteral;

/// 字符串字面量
typedef struct {
    /// 字符串的值
    const char *value;
} StringLiteral;

/// 二元表达式
typedef struct {
    /// 操作符
    const char *operator;
} BinaryExpression;

/// 实例变量申明节点
/// @param name 变量名
/// @return 变量申明
Node *nodeVarDeclareNew(const char *name);

/// 创建访问变量节点
/// @param name 变量名
/// @param var 变量信息
Node *nodeCallVariableNew(const char *name, const Node *var);

/// 创建数字字面量节点
/// @param val 字面量值
/// @param number 数值
/// @param unit 单位
/// @return 数字字面量
Node *nodeNumberLiteralNew(const char *val, double number, const char *unit);

/// 创建字符串字面量节点
/// @param val 字面量值
/// @return 字符串字面量
Node *nodeStringLiteralNew(const char *val);

/// 创建二元表达式
/// @param op 操作符
/// @param left 左值
/// @param right 右值
Node *nodeBinaryExpressionNew(const char *op, Node *left, Node *right);

#endif
