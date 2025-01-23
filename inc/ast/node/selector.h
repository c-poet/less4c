#ifndef LESS4C_AST_NODE_SELECTOR_H
#define LESS4C_AST_NODE_SELECTOR_H

#include "node.h"

/// 选择器
typedef struct {
    BASE_NODE

    /// 选择序列
    List *children;
} Selector;

Selector *selectorNew();

BOOL selectorAddChild(Selector *selector, Node *child);

void selectorPrint(Selector *selector, int level);

void selectorDel(Selector *selector);

#endif
