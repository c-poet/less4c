#include "inc/ast/node/declaration.h"
#include <malloc.h>
#include <stdio.h>

Declaration *declarationNew(char *property, Node *value) {
    Declaration *declaration = malloc(sizeof(Declaration));
    if (!declaration) {
        return NULL;
    }
    nodeInit((POINTER) declaration);
    declaration->type = NT_Declaration;
    declaration->property = property;
    declaration->important = BOOL_FALSE;
    declaration->value = value;
    declaration->print = (POINTER) declarationPrint;
    declaration->destroy = (POINTER) declarationDel;
    value->parent = (POINTER) declaration;
    return declaration;
}

void declarationPrint(Declaration *declaration, int level) {
    nodePrintTypeByLevel((POINTER) declaration, level);
    printf("[property=%s,important=%d]", declaration->property, declaration->important);
    nodePrintByLevel(declaration->value, level + 1);
}

void declarationDel(Declaration *declaration) {
    if (declaration) {
        nodeDel(declaration->value);
        free(declaration);
    }
}
