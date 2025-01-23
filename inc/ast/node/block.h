#ifndef LESS4C_AST_NODE_BLOCK_H
#define LESS4C_AST_NODE_BLOCK_H

#include "node.h"

/// 规则块
typedef struct {
    BASE_NODE

    /// 规则列表
    List *children;
} Block;

/// 创建块
/// @return 块节点
Block *blockNew();

/// 块添加子节点
/// @param block 块
/// @param child 子节点
/// @return 是否添加成功
BOOL blockAddChild(Block *block, Node *child);

/// 块获取所有子节点
/// @param block 块
/// @return 子节点列表
List *blockGetChildren(Block *block);

/// 打印块
/// @param block 块
/// @param level 层级
void blockPrint(Block *block, int level);

/// 释放块
/// @param block 块
void blockDel(Block *block);

#endif
