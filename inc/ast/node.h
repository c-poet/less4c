#ifndef LESS4C_AST_NODE_H
#define LESS4C_AST_NODE_H

#include "inc/core/global.h"

/// 每次扩容节点预留长度
#define NODE_CHILD_R_LEN 20

/// 节点类型
typedef enum {
    /// 根节点
    NT_StyleSheet,
    /// 变量声明
    NT_VarDeclare,
    /// 数量字面量
    NT_NumberLiteral,
    /// 字符串字面量
    NT_StringLiteral,
} NodeType;

/// 节点
typedef struct S_Node {
    /// 类型
    NodeType type;
    /// 子级个数
    int childNum;
    /// 实现已划分的大小
    int actualChildNum;
    /// 具体实现
    POINTER achiever;
    /// 节点父级
    struct S_Node *parent;
    /// 节点子级列表
    struct S_Node **children;
} Node;

/// 创建节点
/// @param type 节点类型
/// @param achiever 具体实现
/// @return 节点
Node *nodeNew(NodeType type, POINTER achiever);

/// 添加子节点
/// @param parent 父节点
/// @param child 子节点
/// @return 是否添加成功
BOOL nodeAddChild(Node *parent, Node *child);

/// 插入节点
/// @param parent 父节点
/// @param child 子节点
/// @param index 插入的下标
/// @return 是否插入成功
BOOL nodeInsertChild(Node *parent, Node *child, int index);

/// 打印节点
/// @param node 节点
void nodePrint(Node *node);

/// 释放节点
/// @param node 节点
void nodeDel(Node *node);

/// 节点类型转字符串
/// @param type 节点类型
/// @return 字符串
char *nodeTypeAsString(NodeType type);

#endif
