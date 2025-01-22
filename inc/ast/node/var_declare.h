#ifndef LESS4C_AST_NODE_VAR_DECLARE_H
#define LESS4C_AST_NODE_VAR_DECLARE_H

#include "node.h"
#include "inc/core/list.h"

/// 变量声明
typedef struct {
    BASE_NODE

    /// 变量名
    const char *name;
    /// 变量值列表
    List *children;
} VarDeclare;

/// 实例变量申明节点
/// @param name 变量名
/// @return 变量申明
VarDeclare *varDeclareNew(const char *name);

BOOL varDeclareAddChild(VarDeclare *varDeclare, Node *child);

void varDeclarePrint(VarDeclare *varDeclare, int level);

void varDeclareDel(VarDeclare *varDeclare);

#endif
