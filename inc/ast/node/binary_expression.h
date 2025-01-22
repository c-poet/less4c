#ifndef LESS4C_AST_NODE_BINARY_EXPRESSION_H
#define LESS4C_AST_NODE_BINARY_EXPRESSION_H

#include "node.h"

/// 二元表达式
typedef struct {
    BASE_NODE

    /// 操作符
    char *operator;
    /// 操作左值
    Node *left;
    /// 操作右值
    Node *right;
} BinaryExpression;

/// 创建二元表达式
/// @param op 操作符
/// @param left 左值
/// @param right 右值
BinaryExpression *binaryExpressionNew(char *op, Node *left, Node *right);

void binaryExpressionPrint(BinaryExpression *binaryExpression, int level);

void binaryExpressionDel(BinaryExpression *binaryExpression);

#endif
