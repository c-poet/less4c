#include "inc/ast/node/call_variable.h"
#include <malloc.h>
#include <stdio.h>

CallVariable *callVariableNew(const char *name, const Node *var) {
    CallVariable *callDeclare = malloc(sizeof(CallVariable));
    if (!callDeclare) {
        return NULL;
    }
    nodeInit((POINTER) callDeclare);
    callDeclare->type = NT_CallVariable;
    callDeclare->name = name;
    callDeclare->var = var;
    callDeclare->print = (POINTER) callVariablePrint;
    callDeclare->destroy = (POINTER) callVariableDel;
    return callDeclare;
}

void callVariablePrint(CallVariable *callVariable, int level) {
    nodePrintTypeByLevel((POINTER) callVariable, level);
    printf("[name=%s]", callVariable->name);
}

void callVariableDel(CallVariable *callVariable) {
    free(callVariable);
}
