#include "inc/ast/node/rule.h"
#include <malloc.h>

Rule *ruleNew(Node *prelude, Node *block) {
    Rule *rule = malloc(sizeof(Rule));
    if (!rule) {
        return rule;
    }
    nodeInit((POINTER) rule);
    rule->type = NT_RULE;
    rule->prelude = prelude;
    rule->block = block;
    rule->print = (POINTER) rulePrint;
    rule->destroy = (POINTER) ruleDel;
    prelude->parent = (POINTER) rule;
    block->parent = (POINTER) rule;
    return rule;
}

void rulePrint(Rule *rule, int level) {
    nodePrintTypeByLevel((POINTER) rule, level);
    nodePrintByLevel(rule->prelude, level + 1);
    nodePrintByLevel(rule->block, level + 1);
}

void ruleDel(Rule *rule) {
    if (rule) {
        nodeDel(rule->prelude);
        nodeDel(rule->block);
        free(rule);
    }
}
