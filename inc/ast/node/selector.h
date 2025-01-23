#ifndef LESS4C_AST_NODE_SELECTOR_H
#define LESS4C_AST_NODE_SELECTOR_H

#include "node.h"

/// 选择器
typedef struct {
    BASE_NODE

    /// 选择序列
    List *children;
} Selector;

/// 创建选择器
/// @return 选择器
Selector *selectorNew();

/// 选择器添加子节点
/// @param selector 选择器
/// @param child 子节点
/// @return 是否添加成功
BOOL selectorAddChild(Selector *selector, Node *child);

/// 选择器打印
/// @param selector 选择器
/// @param level 层级
void selectorPrint(Selector *selector, int level);

/// 释放选择器
/// @param selector 选择器节点
void selectorDel(Selector *selector);

#endif
