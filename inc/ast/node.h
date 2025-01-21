#ifndef LESS4C_AST_NODE_H
#define LESS4C_AST_NODE_H

#include "inc/core/global.h"
#include "inc/core/list.h"

/// 节点类型
typedef enum {
    /// 根节点
    NT_StyleSheet,
    /// 变量声明
    NT_VarDeclare,
    /// 访问变量
    NT_CallVariable,
    /// 数量字面量
    NT_NumberLiteral,
    /// 字符串字面量
    NT_StringLiteral,
    /// 二元操作表达式
    NT_BinaryExpression,
} NodeType;

/// 节点
typedef struct S_Node {
    /// 节点类型
    NodeType type;
    /// 具体实现
    POINTER achiever;
    /// 节点父级
    struct S_Node *parent;
    /// 节点子级列表
    List *children;

    /// 打印调用的函数
    void (*print)(POINTER, int);

    /// 释放调用函数
    void (*destroy)(POINTER);
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
void nodePrint(const Node *node);

/// 打印节点
/// @param node 节点
/// @param level 层次
void nodePrintByLevel(const Node *node, int level);

/// 释放节点
/// @param node 节点
void nodeDel(Node *node);

/// 节点类型转字符串
/// @param type 节点类型
/// @return 字符串
char *nodeTypeAsString(NodeType type);

#endif
