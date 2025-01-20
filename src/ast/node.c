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
    node->childNum = 0;
    node->actualChildNum = 0;
    node->children = NULL;
    return node;
}

BOOL nodeAddChild(Node *parent, Node *child) {
    return nodeInsertChild(parent, child, parent->childNum);
}

BOOL nodeInsertChild(Node *parent, Node *child, int index) {
    if (index < 0 || parent->childNum < index) {
        return BOOL_FALSE;
    }
    if (parent->children == NULL) {
        parent->actualChildNum = NODE_CHILD_R_LEN + 1;
        parent->children = malloc(sizeof(Node *) * parent->actualChildNum);
        if (!parent->children) {
            return BOOL_FALSE;
        }
    } else if (parent->childNum + 1 >= parent->actualChildNum) {
        parent->actualChildNum = NODE_CHILD_R_LEN + 1 + parent->childNum;
        Node **children = realloc(parent->children, sizeof(Node *) * parent->actualChildNum);
        if (!children) {
            return BOOL_FALSE;
        }
        parent->children = children;
    }
    if (parent->childNum == index) {
        parent->children[parent->childNum] = child;
    } else {
        int i = child->childNum;
        while (i > index) {
            parent->children[i] = parent->children[i - 1];
            --i;
        }
        parent->children[index] = child;
    }
    child->parent = parent;
    ++parent->childNum;
    return BOOL_TRUE;
}

void printTab(int num) {
    while (num > 0) {
        printf("\t");
        --num;
    }
}

void doNodePrint(Node *node, int level) {
    printTab(level);
    printf("-[%s]\n", nodeTypeAsString(node->type));
    int i = 0;
    while (i < node->childNum) {
        doNodePrint(node->children[i], level + 1);
        ++i;
    }
}

void nodePrint(Node *node) {
    doNodePrint(node, 0);
}

void nodeDel(Node *node) {
    if (node) {
        while (--node->childNum >= 0) {
            nodeDel(node->children[node->childNum]);
        }
        free(node->achiever);
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
        case NT_NumberLiteral:
            return "NumberLiteral";
        case NT_StringLiteral:
            return "StringLiteral";
        default:
            return "";
    }
}
