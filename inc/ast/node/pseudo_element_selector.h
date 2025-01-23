#ifndef LESS4C_AST_NODE_PSEUDO_ELEMENT_SELECTOR_H
#define LESS4C_AST_NODE_PSEUDO_ELEMENT_SELECTOR_H

#include "node.h"

/// 伪元素选择器
typedef struct {
    BASE_NODE

    /// 名称
    char *name;
} PseudoElementSelector;

/// 创建伪元素选择器
/// @param name 名称
/// @return 伪元素选择器
PseudoElementSelector *pseudoElementSelectorNew(char *name);

/// 打印伪元素选择器
/// @param pseudoElementSelector 选择器
/// @param level 层级
void pseudoElementSelectorPrint(PseudoElementSelector *pseudoElementSelector, int level);

/// 释放伪元素选择器
/// @param pseudoElementSelector 伪元素选择器
void pseudoElementSelectorDel(PseudoElementSelector *pseudoElementSelector);

#endif
