#include "inc/ast/node/selectors.h"
#include "malloc.h"

Selectors *selectorsNew() {
    Selectors *selectors = malloc(sizeof(Selectors));
    if (!selectors) {
        return NULL;
    }
    nodeInit((POINTER) selectors);
    selectors->type = NT_Selectors;
    selectors->print = (POINTER) selectorsPrint;
    selectors->destroy = (POINTER) selectorsDel;
    selectors->addChild = (POINTER) selectorsAddChild;
    selectors->children = listNew(sizeof(Node *));
    if (!selectors->children) {
        selectorsDel(selectors);
        return NULL;
    }
    return selectors;
}

BOOL selectorsAddChild(Selectors *selectors, Node *child) {
    return listAdd(selectors->children, child);
}

void selectorsPrint(Selectors *selectors, int level) {
    nodePrintTypeByLevel((POINTER) selectors, level);
    nodeListPrintByLevel(selectors->children, level + 1);
}

void selectorsDel(Selectors *selectors) {
    if (selectors) {
        nodeListDel(selectors->children);
        listDel(selectors->children);
        free(selectors);
    }
}
