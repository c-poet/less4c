#include "inc/ast/node/pseudo_class_selector.h"
#include "inc/core/func.h"
#include <malloc.h>
#include <stdio.h>

PseudoClassSelector *pseudoClassSelectorNew(char *name) {
    PseudoClassSelector *pseudoClassSelector = malloc(sizeof(PseudoClassSelector));
    if (!pseudoClassSelector) {
        return NULL;
    }
    nodeInit((POINTER) pseudoClassSelector);
    pseudoClassSelector->type = NT_PseudoClassSelector;
    pseudoClassSelector->print = (POINTER) pseudoClassSelectorPrint;
    pseudoClassSelector->destroy = (POINTER) pseudoClassSelectorDel;
    pseudoClassSelector->name = charsClone(name);
    return pseudoClassSelector;
}

void pseudoClassSelectorPrint(PseudoClassSelector *pseudoClassSelector, int level) {
    nodePrintTypeByLevel((POINTER) pseudoClassSelector, level);
    printf("[name=%s]", pseudoClassSelector->name);
}

void pseudoClassSelectorDel(PseudoClassSelector *pseudoClassSelector) {
    if (pseudoClassSelector) {
        free(pseudoClassSelector->name);
        free(pseudoClassSelector);
    }
}
