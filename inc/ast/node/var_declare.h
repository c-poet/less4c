#ifndef LESS4C_AST_NODE_VAR_DECLARE_H
#define LESS4C_AST_NODE_VAR_DECLARE_H

#include "node.h"
#include "inc/core/list.h"

/// 变量声明
typedef struct {
    BASE_NODE

    /// 变量名
    char *name;
    /// 变量值
    Node *value;
} VarDeclare;

/// 实例变量申明节点
/// @param name 变量名
/// @return 变量申明
VarDeclare *varDeclareNew(char *name, Node *value);

/// 打印变量声明
/// @param varDeclare 变量声明
/// @param level 层级
void varDeclarePrint(VarDeclare *varDeclare, int level);

/// 释放变量声明
/// @param varDeclare 变量声明
void varDeclareDel(VarDeclare *varDeclare);

#endif
