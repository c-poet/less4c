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
    node->children = NULL;
    return node;
}

BOOL nodeAddChild(Node *parent, Node *child) {
    if (parent->children == NULL) {
        parent->children = listNew(sizeof(Node *));
        if (!parent->children) {
            return BOOL_FALSE;
        }
    }
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

void nodePrint(const Node *node) {
    nodePrintByLevel(node, 0);
}

void nodePrintByLevel(const Node *node, int level) {
    printTab(level);
    printf("- %s", nodeTypeAsString(node->type));
    if (node->print != NULL) {
        node->print(node->achiever, level);
    }
    if (!listEmpty(node->children)) {
        int i = 0;
        while (i < node->children->size) {
            nodePrintByLevel(node->children->values[i], level + 1);
            ++i;
        }
    }
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
        case NT_RULE:
            return "Rule";
        case NT_Block:
            return "Block";
        case NT_SelectorList:
            return "SelectorList";
        case NT_Selector:
            return "Selector";
        case NT_TypeSelector:
            return "TypeSelector";
        case NT_IdSelector:
            return "IdSelector";
        case NT_ClassSelector:
            return "ClassSelector";
        case NT_PseudoClassSelector:
            return "PseudoClassSelector";
        case NT_PseudoElementSelector:
            return "PseudoElementSelector";
        default:
            return "";
    }
}
