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

/// 添加子节点
/// @param styleSheet 样式表
/// @param child 子节点
void styleSheetAddChild(StyleSheet *styleSheet, Node *child);

/// 获取子节点列表
/// @param styleSheet 样式表
/// @return 子节点列表
List *styleSheetGetChildren(StyleSheet *styleSheet);

/// 打印样式表
/// @param styleSheet 样式表
/// @param level 层级
void styleSheetPrint(StyleSheet *styleSheet, int level);

/// 释放样式表
/// @param styleSheet 样式表
void styleSheetDel(StyleSheet *styleSheet);

#endif
