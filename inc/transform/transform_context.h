#ifndef LESS4C_TRANSFORM_CONTEXT_H
#define LESS4C_TRANSFORM_CONTEXT_H

#include "inc/ast/ast.h"
#include "inc/core/map.h"
#include "transform_config.h"

/// 转换上下文
typedef struct S_TransformContext {
    /// 目标节点
    Node *targetNode;
    /// 源节点
    Node *sourceNode;
    /// 目标语法树
    Ast *targetAst;
    /// 源语法树
    Ast *sourceAst;
    /// 变量表
    Map *varTable;
    /// 配置
    TransformConfig *config;
    /// 父级上下文
    struct S_TransformContext *parent;
} TransformContext;

/// 创建转换上下文
/// @param config 转换配置
/// @param targetAst 目标语法树
/// @param sourceAst 源语法树
TransformContext *transformContextNew(TransformConfig *config, Ast *targetAst, Ast *sourceAst);

/// 释放转换上下文
/// @param context 上下文
void transformContextDel(TransformContext *context);

#endif
