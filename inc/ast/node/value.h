#ifndef LESS4C_AST_NODE_VALUE_H
#define LESS4C_AST_NODE_VALUE_H

#include "node.h"

/// 值节点
typedef struct {
    BASE_NODE

    /// 子节点列表
    List *children;
} Value;

/// 创建值节点
/// @return 值节点
Value *valueNew();

/// 添加下级
/// @param value 值
/// @param child 下级节点
void valueAddChild(Value *value, Node *child);

/// 获取下级节点列表
/// @param value 值
/// @return 下级节点列表
List *valueGetChildren(Value *value);

/// 打印值节点
/// @param value 值节点
/// @param level 层级
void valuePrint(Value *value, int level);

/// 释放值节点
/// @param value 值节点
void valueDel(Value *value);

#endif
