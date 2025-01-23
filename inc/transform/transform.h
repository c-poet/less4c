#ifndef LESS4C_TRANSFORM_H
#define LESS4C_TRANSFORM_H

#include "inc/ast/ast.h"

/// 转换成Css语法树
/// @param lessAst less语法树
/// @return Css语法树
Ast *transformToCssAst(Ast *lessAst);

#endif
