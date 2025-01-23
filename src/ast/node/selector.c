#include "inc/ast/node/selector.h"
#include <malloc.h>

Selector *selectorNew() {
    Selector *selector = malloc(sizeof(Selector));
    if (!selector) {
        return NULL;
    }
    nodeInit((POINTER) selector);
    selector->type = NT_Selector;
    selector->addChild = (POINTER) selectorAddChild;
    selector->print = (POINTER) selectorPrint;
    selector->destroy = (POINTER) selectorDel;
    selector->children = listNew(sizeof(Node *));
    if (!selector->children) {
        selectorDel(selector);
        return NULL;
    }
    return selector;
}

BOOL selectorAddChild(Selector *selector, Node *child) {
    return listAdd(selector->children, child);
}

void selectorPrint(Selector *selector, int level) {
    nodePrintTypeByLevel((POINTER) selector, level);
    nodeListPrintByLevel(selector->children, level + 1);
}

void selectorDel(Selector *selector) {
    if (selector) {
        nodeListDel(selector->children);
        listDel(selector->children);
        free(selector);
    }
}

