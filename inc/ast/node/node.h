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
    /// 规则
    NT_RULE,
    /// 块
    NT_Block,
    /// 元素选择列表
    NT_Selectors,
    /// 选择器
    NT_Selector,
    /// 类型选择器
    NT_TypeSelector,
    /// ID选择器
    NT_IdSelector,
    /// 类选择器
    NT_ClassSelector,
    /// 伪类选择器
    NT_PseudoClassSelector,
    /// 伪元素选择
    NT_PseudoElementSelector,
} NodeType;

/// 节点基本结构定义
#define BASE_NODE \
    NodeType type;\
    struct ParseContext *context; \
    struct S_Node *parent; \
    BOOL (*addChild)(struct S_Node*, struct S_Node*); \
    void (*print)(struct S_Node*, int);               \
    void (*destroy)(struct S_Node*);

/// 普通节点
typedef struct S_Node {
    BASE_NODE
} Node;

/// 节点信息初始化
/// @param context 上下文信息
/// @param node 节点
void nodeInit(Node *node);

/// 添加子节点
/// @param parent 父节点
/// @param child 子节点
/// @return 是否添加成功
BOOL nodeAddChild(Node *parent, Node *child);

/// 打印指定数据的制表符
/// @param num 打印的数量
void nodePrintTab(int num);

/// 打印节点
/// @param node 节点
void nodePrint(Node *node);

/// 打印节点类型
/// @param node 节点
/// @param level 层次
void nodePrintTypeByLevel(Node *node, int level);

void nodePrintByLevel(Node *node, int level);

void nodeListPrintByLevel(List *nodes, int level);

/// 释放节点
/// @param node 节点
void nodeDel(Node *node);

void nodeListDel(List *nodes);

/// 节点类型转字符串
/// @param type 节点类型
/// @return 字符串
char *nodeTypeAsString(NodeType type);

#endif
