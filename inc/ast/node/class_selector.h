#ifndef LESS4C_AST_NODE_CLASS_SELECTOR_H
#define LESS4C_AST_NODE_CLASS_SELECTOR_H

#include "node.h"

/// 类选择器
typedef struct {
    BASE_NODE

    /// 选择器名称
    char *name;
} ClassSelector;

/// 创建类选择器
/// @param name 选择器名称
/// @return 类选择器
ClassSelector *classSelectorNew(char *name);

/// 打印类选择器
/// @param classSelector 类选择器
/// @param level 层级
void classSelectorPrint(ClassSelector *classSelector, int level);

/// 释放类选择器
/// @param classSelector 类选择器
void classSelectorDel(ClassSelector *classSelector);

#endif
