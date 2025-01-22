#include "inc/ast/node/var_declare.h"
#include <malloc.h>
#include <stdio.h>

VarDeclare *varDeclareNew(const char *name) {
    VarDeclare *varDeclare = malloc(sizeof(VarDeclare));
    if (!varDeclare) {
        return NULL;
    }
    nodeInit((POINTER) varDeclare);
    varDeclare->type = NT_VarDeclare;
    varDeclare->name = name;
    varDeclare->addChild = (POINTER) varDeclareAddChild;
    varDeclare->print = (POINTER) varDeclarePrint;
    varDeclare->destroy = (POINTER) varDeclareDel;
    varDeclare->children = listNew(sizeof(Node *));
    if (varDeclare->children == NULL) {
        varDeclareDel(varDeclare);
        return NULL;
    }
    return varDeclare;
}

BOOL varDeclareAddChild(VarDeclare *varDeclare, Node *child) {
    return listAdd(varDeclare->children, child);
}

void varDeclarePrint(VarDeclare *varDeclare, int level) {
    nodePrintTypeByLevel((POINTER) varDeclare, level);
    printf("[name=%s]", varDeclare->name);
    nodeListPrintByLevel(varDeclare->children, level + 1);
}

void varDeclareDel(VarDeclare *varDeclare) {
    if (varDeclare) {
        nodeListDel(varDeclare->children);
        free(varDeclare->children);
        free(varDeclare);
    }
}
