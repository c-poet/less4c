#ifndef LESS4C_TRANSFORM_CONTEXT_H
#define LESS4C_TRANSFORM_CONTEXT_H

#include "inc/ast/ast.h"

/// 转换上下文
typedef struct {
    /// 目标节点
    Node *targetNode;
    /// 源节点
    Node *sourceNode;
    /// 目标语法树
    Ast *targetAst;
    /// 源语法树
    Ast *sourceAst;
} TransformContext;


#endif
