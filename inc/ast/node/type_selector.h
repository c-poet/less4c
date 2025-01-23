#ifndef LESS4C_AST_NODE_TYPE_SELECTOR_H
#define LESS4C_AST_NODE_TYPE_SELECTOR_H

#include "node.h"

/// 类选择器
typedef struct {
    BASE_NODE

    /// 选择器名称
    char *name;
} TypeSelector;

/// 创建类型选择器
/// @param name 选择器名称
/// @return 类型选择器
TypeSelector *typeSelectorNew(char *name);

/// 打印类型选择器
/// @param typeSelector 类型选择器
/// @param level 层级
void typeSelectorPrint(TypeSelector *typeSelector, int level);

/// 释放类型选择器
/// @param typeSelector 类型选择器
void typeSelectorDel(TypeSelector *typeSelector);

#endif
