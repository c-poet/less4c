#include "inc/ast/node/node.h"
#include <stdio.h>

void nodeInit(Node *node) {
    node->type = NT_StyleSheet;
    node->parent = NULL;
    node->addChild = NULL;
    node->print = NULL;
    node->destroy = NULL;
    node->getChildren = NULL;
}

BOOL nodeAddChild(Node *parent, Node *child) {
    if (parent->addChild != NULL) {
        if (parent->addChild(parent, child)) {
            child->parent = parent;
            return BOOL_TRUE;
        }
    }
    return BOOL_FALSE;
}

void nodePrintTab(int num) {
    while (num > 0) {
        printf("\t");
        --num;
    }
}

void nodePrint(Node *node) {
    nodePrintByLevel(node, 0);
}

void nodePrintTypeByLevel(Node *node, int level) {
    if (level != 0) {
        printf("\n");
    }
    nodePrintTab(level);
    printf("- %s", nodeTypeAsString(node->type));
}

void nodePrintByLevel(Node *node, int level) {
    if (node && node->print != NULL) {
        node->print(node, level);
    }
}

void nodeListPrintByLevel(List *nodes, int level) {
    if (nodes && nodes->size > 0) {
        int i = 0;
        while (i < nodes->size) {
            if (((Node *) nodes->values[i])->print) {
                ((Node *) nodes->values[i])->print(nodes->values[i], level);
            }
            ++i;
        }
    }
}

List *nodeGetChildren(Node *node) {
    if (node && node->getChildren != NULL) {
        return node->getChildren(node);
    }
    return NULL;
}

void nodeDel(Node *node) {
    if (node && node->destroy != NULL) {
        node->destroy(node);
    }
}

void nodeListDel(List *nodes) {
    listEach(nodes, (POINTER) nodeDel);
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
        case NT_Selectors:
            return "Selectors";
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
        case NT_Declaration:
            return "Declaration";
        case NT_Value:
            return "Value";
        case NT_IMPORT:
            return "Import";
        default:
            return "";
    }
}
