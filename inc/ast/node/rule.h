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

Rule *ruleNew(Node *prelude, Node *block);

void rulePrint(Rule *rule, int level);

void ruleDel(Rule *rule);

#endif
