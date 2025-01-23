#ifndef LESS4C_AST_NODE_SELECTORS_H
#define LESS4C_AST_NODE_SELECTORS_H

#include "node.h"

/// 选择器集合
typedef struct {
    BASE_NODE

    /// 选择器列表
    List *children;
} Selectors;

/// 创建选择器列表
/// @return 选择器列表
Selectors *selectorsNew();

/// 添加子节点
/// @param selectors 选择器
/// @param child 子节点
/// @return 是否添加成功
BOOL selectorsAddChild(Selectors *selectors, Node *child);

/// 选择器打印
/// @param selectors 选择器
/// @param level 层级
void selectorsPrint(Selectors *selectors, int level);

/// 释放选择器
/// @param selectors 选择器
void selectorsDel(Selectors *selectors);

#endif
