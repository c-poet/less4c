#include "inc/ast/node.h"
#include <malloc.h>
#include <stdio.h>

Node *nodeNew(NodeType type, POINTER achiever) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->type = type;
    node->achiever = achiever;
    node->parent = NULL;
    node->print = NULL;
    node->destroy = NULL;
    node->children = listNew(sizeof(Node *));
    if (!node->children) {
        nodeDel(node);
        return NULL;
    }
    return node;
}

BOOL nodeAddChild(Node *parent, Node *child) {
    child->parent = parent;
    return listAdd(parent->children, child);
}

BOOL nodeInsertChild(Node *parent, Node *child, int index) {
    child->parent = parent;
    return listInsert(parent->children, index, child);
}

void printTab(int num) {
    while (num > 0) {
        printf("\t");
        --num;
    }
}

void doNodePrint(Node *node, int level) {
    printTab(level);
    printf("- %s", nodeTypeAsString(node->type));
    if (node->print != NULL) {
        printf("[");
        node->print(node->achiever);
        printf("]");
    }
    printf("\n");
    int i = 0;
    while (i < node->children->size) {
        doNodePrint(node->children->values[i], level + 1);
        ++i;
    }
}

void nodePrint(Node *node) {
    doNodePrint(node, 0);
}

void nodeDel(Node *node) {
    if (node) {
        listEach(node->children, (POINTER) nodeDel);
        if (node->destroy != NULL) {
            node->destroy(node->achiever);
        }
        free(node->children);
        free(node);
    }
}

char *nodeTypeAsString(NodeType type) {
    switch (type) {
        case NT_StyleSheet:
            return "StyleSheet";
        case NT_VarDeclare:
            return "VarDeclare";
        case NT_CallVariable:
            return "CallVariable";
        case NT_NumberLiteral:
            return "NumberLiteral";
        case NT_StringLiteral:
            return "StringLiteral";
        case NT_BinaryExpression:
            return "BinaryExpression";
        default:
            return "";
    }
}
