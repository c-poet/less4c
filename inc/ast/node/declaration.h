#ifndef LESS4C_AST_NODE_DECLARATION_H
#define LESS4C_AST_NODE_DECLARATION_H

#include "node.h"

/// 属性声明
typedef struct {
    BASE_NODE

    /// 提升权重
    BOOL important;
    /// 属性名
    char *property;
    /// 属性值
    Node *value;
} Declaration;

/// 创建属性声明
/// @param property 属性名
/// @param value 属性值
/// @return 属性声明
Declaration *declarationNew(char *property, Node *value);

/// 打印属性
/// @param declaration 属性
/// @param level 层级
void declarationPrint(Declaration *declaration, int level);

/// 释放属性内存
/// @param declaration 属性
void declarationDel(Declaration *declaration);

#endif
