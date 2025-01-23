#include "inc/ast/node/type_selector.h"
#include "inc/core/func.h"
#include <malloc.h>
#include <stdio.h>

TypeSelector *typeSelectorNew(char *name) {
    TypeSelector *typeSelector = malloc(sizeof(TypeSelector));
    if (!typeSelector) {
        return NULL;
    }
    nodeInit((POINTER) typeSelector);
    typeSelector->type = NT_TypeSelector;
    typeSelector->name = charsClone(name);
    typeSelector->print = (POINTER) typeSelectorPrint;
    typeSelector->destroy = (POINTER) typeSelectorDel;
    return typeSelector;
}

void typeSelectorPrint(TypeSelector *typeSelector, int level) {
    nodePrintTypeByLevel((POINTER) typeSelector, level);
    printf("[name=%s]", typeSelector->name);
}

void typeSelectorDel(TypeSelector *typeSelector) {
    if (typeSelector) {
        free(typeSelector->name);
        free(typeSelector);
    }
}
