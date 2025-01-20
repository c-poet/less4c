#include "inc/ast/ast.h"
#include <malloc.h>
#include <stdio.h>

Ast *astNew() {
    Node *root = nodeNew(NT_StyleSheet, NULL);
    if (root == NULL) {
        return NULL;
    }
    Ast *ast = malloc(sizeof(Ast));
    if (!ast) {
        nodeDel(root);
        return NULL;
    }
    ast->root = root;
    return ast;
}

void astPrint(Ast *ast) {
    if (ast == NULL || ast->root == NULL) {
        return;
    }
    nodePrint(ast->root);
}

void astDel(Ast *ast) {
    if (ast) {
        nodeDel(ast->root);
        free(ast);
    }
}
