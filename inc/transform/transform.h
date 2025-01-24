#ifndef LESS4C_TRANSFORM_H
#define LESS4C_TRANSFORM_H

#include "inc/ast/ast.h"
#include "inc/transform/transform_config.h"

/// 转换成Css语法树
/// @param config 转换配置
/// @param lessAst less语法树
/// @return Css语法树
Ast *transformToCssAst(TransformConfig *config, Ast *lessAst);

#endif
