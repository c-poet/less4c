#ifndef LESS4C_AST_NODE_IMPORT_H
#define LESS4C_AST_NODE_IMPORT_H

#include "node.h"

/// 导入节点
typedef struct {
    BASE_NODE

    /// 文件名
    char *fileName;
    /// 样式表
    Node *root;
} Import;

/// 创建导入节点
/// @param fileName 文件名
/// @param root 根节点
/// @return 导入节点
Import *importNew(char *fileName, Node *root);

/// 导入节点打印
/// @param import 导入节点
/// @param level 层级
void importPrint(Import *import, int level);

/// 释放导入节点
/// @param import 导入节点
void importDel(Import *import);

#endif
