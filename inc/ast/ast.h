#ifndef LESS4C_AST_H
#define LESS4C_AST_H

#include "node.h"

typedef struct {
    /// 节点列表
    Node *root;
} Ast;

/// 创建语法树
/// @return 语法树
Ast *astNew();

/// 打印语法树
/// @param ast 语法树
void astPrint(Ast *ast);

/// 释放语法树
/// @param ast 语法树
void astDel(Ast *ast);

#endif
