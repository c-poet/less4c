#include "inc/ast/node/style_sheet.h"
#include <malloc.h>
#include <stdio.h>

StyleSheet *styleSheetNew() {
    StyleSheet *styleSheet = malloc(sizeof(StyleSheet));
    if (!styleSheet) {
        return NULL;
    }
    nodeInit((POINTER) styleSheet);
    styleSheet->type = NT_StyleSheet;
    styleSheet->addChild = (POINTER) styleSheetAddChild;
    styleSheet->print = (POINTER) styleSheetPrint;
    styleSheet->destroy = (POINTER) styleSheetDel;
    styleSheet->children = listNew(sizeof(Node *));
    if (styleSheet->children == NULL) {
        styleSheetDel(styleSheet);
        return NULL;
    }
    return styleSheet;
}

void styleSheetAddChild(StyleSheet *styleSheet, Node *child) {
    listAdd(styleSheet->children, child);
}

void styleSheetPrint(StyleSheet *styleSheet, int level) {
    nodePrintTypeByLevel((POINTER) styleSheet, level);
    printf("[AST]");
    nodeListPrintByLevel(styleSheet->children, level + 1);
}

void styleSheetDel(StyleSheet *styleSheet) {
    if (styleSheet) {
        nodeListDel(styleSheet->children);
        free(styleSheet->children);
        free(styleSheet);
    }
}
