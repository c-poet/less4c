#include "inc/ast/ast.h"
#include <malloc.h>
#include <stdio.h>
#include "inc/ast/node/style_sheet.h"

Ast *astNew() {
    StyleSheet *styleSheet = styleSheetNew();
    if (styleSheet == NULL) {
        return NULL;
    }
    Ast *ast = malloc(sizeof(Ast));
    if (!ast) {
        styleSheetDel(styleSheet);
        return NULL;
    }
    ast->root = (POINTER) styleSheet;
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
