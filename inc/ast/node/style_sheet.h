#ifndef LESS4C_AST_NODE_STYLE_SHEET_H
#define LESS4C_AST_NODE_STYLE_SHEET_H

#include "node.h"
#include "inc/core/list.h"

/// 样式表
typedef struct {
    BASE_NODE

    /// 子节点
    List *children;
} StyleSheet;

/// 创建样式表节点
/// @return 样式表
StyleSheet *styleSheetNew();

void styleSheetAddChild(StyleSheet *styleSheet, Node *child);

void styleSheetPrint(StyleSheet *styleSheet, int level);

void styleSheetDel(StyleSheet *styleSheet);

#endif
