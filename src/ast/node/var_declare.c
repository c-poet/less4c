#include "inc/ast/node/var_declare.h"
#include "inc/core/func.h"
#include <malloc.h>
#include <stdio.h>

VarDeclare *varDeclareNew(char *name, Node *value) {
    VarDeclare *varDeclare = malloc(sizeof(VarDeclare));
    if (!varDeclare) {
        return NULL;
    }
    nodeInit((POINTER) varDeclare);
    varDeclare->type = NT_VarDeclare;
    varDeclare->name = charsClone(name);
    varDeclare->print = (POINTER) varDeclarePrint;
    varDeclare->destroy = (POINTER) varDeclareDel;
    varDeclare->value = value;
    value->parent = (POINTER) varDeclare;
    return varDeclare;
}

void varDeclarePrint(VarDeclare *varDeclare, int level) {
    nodePrintTypeByLevel((POINTER) varDeclare, level);
    printf("[name=%s]", varDeclare->name);
    nodePrintByLevel(varDeclare->value, level + 1);
}

void varDeclareDel(VarDeclare *varDeclare) {
    if (varDeclare) {
        nodeDel(varDeclare->value);
        free(varDeclare->name);
        free(varDeclare);
    }
}
