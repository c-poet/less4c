#ifndef LESS4C_AST_NODE_SELECTORS_H
#define LESS4C_AST_NODE_SELECTORS_H

#include "node.h"

/// 选择器集合
typedef struct {
    BASE_NODE

    /// 选择器列表
    List *children;
} Selectors;

Selectors *selectorsNew();

BOOL selectorsAddChild(Selectors *selectors, Node *child);

void selectorsPrint(Selectors *selectors, int level);

void selectorsDel(Selectors *selectors);

#endif
