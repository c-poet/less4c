#ifndef LESS4C_AST_NODE_RULE_H
#define LESS4C_AST_NODE_RULE_H

#include "node.h"

/// 规则
typedef struct {
    BASE_NODE

    /// 选择器列表
    Node *prelude;
    /// 规则块
    Node *block;
} Rule;

/// 创建规则
/// @param prelude 选择器列表
/// @param block 规则块
Rule *ruleNew(Node *prelude, Node *block);

/// 规则打印
/// @param rule 规则
/// @param level 层级
void rulePrint(Rule *rule, int level);

/// 释放规则
/// @param rule 规则
void ruleDel(Rule *rule);

#endif
