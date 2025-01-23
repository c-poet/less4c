#ifndef LESS4C_AST_NODE_ID_SELECTOR_H
#define LESS4C_AST_NODE_ID_SELECTOR_H

#include "node.h"

/// Id选择器
typedef struct {
    BASE_NODE

    /// Id名称
    char *name;
} IdSelector;

/// 创建Id选择器
/// @param name 选择器名称
/// @return id选择器
IdSelector *idSelectorNew(char *name);

/// 打印Id选择器
/// @param idSelector Id选择器
/// @param level 层级
void idSelectorPrint(IdSelector *idSelector, int level);

/// 释放Id选择器
/// @param idSelector Id选择器
void idSelectorDel(IdSelector *idSelector);

#endif
