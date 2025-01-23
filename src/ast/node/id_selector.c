#include "inc/ast/node/id_selector.h"
#include <malloc.h>
#include <stdio.h>

IdSelector *idSelectorNew(char *name) {
    IdSelector *idSelector = malloc(sizeof(IdSelector));
    if (!idSelector) {
        return NULL;
    }
    nodeInit((POINTER) idSelector);
    idSelector->type = NT_IdSelector;
    idSelector->name = name;
    idSelector->print = (POINTER) idSelectorPrint;
    idSelector->destroy = (POINTER) idSelectorDel;
    return idSelector;
}

void idSelectorPrint(IdSelector *idSelector, int level) {
    nodePrintTypeByLevel((POINTER) idSelector, level);
    printf("[name=%s]", idSelector->name);
}

void idSelectorDel(IdSelector *idSelector) {
    if (idSelector) {
        free(idSelector);
    }
}
