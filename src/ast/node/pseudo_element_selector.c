#include "inc/ast/node/pseudo_element_selector.h"
#include <malloc.h>
#include <stdio.h>

PseudoElementSelector *pseudoElementSelectorNew(char *name) {
    PseudoElementSelector *pseudoElementSelector = malloc(sizeof(PseudoElementSelector));
    if (!pseudoElementSelector) {
        return NULL;
    }
    nodeInit((POINTER) pseudoElementSelector);
    pseudoElementSelector->type = NT_PseudoElementSelector;
    pseudoElementSelector->print = (POINTER) pseudoElementSelectorPrint;
    pseudoElementSelector->destroy = (POINTER) pseudoElementSelectorDel;
    pseudoElementSelector->name = name;
    return pseudoElementSelector;
}

void pseudoElementSelectorPrint(PseudoElementSelector *pseudoElementSelector, int level) {
    nodePrintTypeByLevel((POINTER) pseudoElementSelector, level);
    printf("[name=%s]", pseudoElementSelector->name);
}

void pseudoElementSelectorDel(PseudoElementSelector *pseudoElementSelector) {
    if (pseudoElementSelector) {
        free(pseudoElementSelector);
    }
}

