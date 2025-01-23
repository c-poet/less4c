#include "inc/ast/node/class_selector.h"
#include <malloc.h>
#include <stdio.h>

ClassSelector *classSelectorNew(char *name) {
    ClassSelector *classSelector = malloc(sizeof(ClassSelector));
    if (!classSelector) {
        return NULL;
    }
    nodeInit((POINTER) classSelector);
    classSelector->type = NT_ClassSelector;
    classSelector->name = name;
    classSelector->print = (POINTER) classSelectorPrint;
    classSelector->destroy = (POINTER) classSelectorDel;
    return classSelector;
}

void classSelectorPrint(ClassSelector *classSelector, int level) {
    nodePrintTypeByLevel((POINTER) classSelector, level);
    printf("[name=%s]", classSelector->name);
}

void classSelectorDel(ClassSelector *classSelector) {
    if (classSelector) {
        free(classSelector);
    }
}
