#ifndef LESS4C_AST_NODE_CALL_VARIABLE_H
#define LESS4C_AST_NODE_CALL_VARIABLE_H

#include "node.h"

/// 调用变量
typedef struct {
    BASE_NODE

    /// 变量名
    const char *name;
    /// 变量所在节点
    const Node *var;
} CallVariable;

/// 创建访问变量节点
/// @param name 变量名
/// @param var 变量信息
CallVariable *callVariableNew(const char *name, const Node *var);

void callVariablePrint(CallVariable *callVariable, int level);

void callVariableDel(CallVariable *callVariable);


#endif
