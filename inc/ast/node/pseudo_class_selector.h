#ifndef LESS4C_AST_NODE_PSEUDO_CLASS_SELECTOR_H
#define LESS4C_AST_NODE_PSEUDO_CLASS_SELECTOR_H

#include "node.h"

/// 伪类选择器
typedef struct {
    BASE_NODE

    /// 名称
    char *name;
} PseudoClassSelector;

/// 创建伪类选择器
/// @param name 名称
/// @return 伪类选择器
PseudoClassSelector *pseudoClassSelectorNew(char *name);

/// 打印伪类选择器
/// @param pseudoClassSelector 选择器
/// @param level 层级
void pseudoClassSelectorPrint(PseudoClassSelector *pseudoClassSelector, int level);

/// 释放伪类选择器
/// @param pseudoClassSelector 伪类选择器
void pseudoClassSelectorDel(PseudoClassSelector *pseudoClassSelector);

#endif
