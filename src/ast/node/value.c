#include "inc/ast/node/value.h"
#include <malloc.h>

Value *valueNew() {
    Value *value = malloc(sizeof(Value));
    if (!value) {
        return NULL;
    }
    nodeInit((POINTER) value);
    value->type = NT_Value;
    value->print = (POINTER) valuePrint;
    value->destroy = (POINTER) valueDel;
    value->addChild = (POINTER) valueAddChild;
    value->getChildren = (POINTER) valueGetChildren;
    value->children = listNew(sizeof(Node *));
    if (value->children == NULL) {
        valueDel(value);
        return NULL;
    }
    return value;
}

void valueAddChild(Value *value, Node *child) {
    listAdd(value->children, child);
}

List *valueGetChildren(Value *value) {
    return value->children;
}

void valuePrint(Value *value, int level) {
    nodePrintTypeByLevel((POINTER) value, level);
    nodeListPrintByLevel(value->children, level + 1);
}

void valueDel(Value *value) {
    if (value) {
        nodeListDel(value->children);
        listDel(value->children);
        free(value);
    }
}
