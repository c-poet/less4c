#ifndef LESS4C_AST_PARSE_FUNC_PRIVATE_H
#define LESS4C_AST_PARSE_FUNC_PRIVATE_H

#include "parse_context.h"
#include "inc/core/list.h"

/// 查询上下文中变量定义的节点
/// @param context 上下文
/// @param name 变量名
/// @return 节点
Node *findVariable(ParseContext *context, const char *name);

/// 判断当前token是否是在块开始之前
/// @param context 上下文
/// @return 是否在块开始之前
BOOL isRulePrelude(ParseContext *context);

#endif
