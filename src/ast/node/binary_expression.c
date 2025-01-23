#include "inc/ast/node/binary_expression.h"
#include "inc/core/func.h"
#include <stdio.h>
#include <malloc.h>

BinaryExpression *binaryExpressionNew(char *op, Node *left, Node *right) {
    BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
    if (!binaryExpression) {
        return NULL;
    }
    nodeInit((POINTER) binaryExpression);
    binaryExpression->type = NT_BinaryExpression;
    binaryExpression->operator = charsClone(op);
    binaryExpression->left = left;
    binaryExpression->right = right;
    binaryExpression->print = (POINTER) binaryExpressionPrint;
    binaryExpression->destroy = (POINTER) binaryExpressionDel;
    left->parent = (POINTER) binaryExpression;
    right->parent = (POINTER) binaryExpression;
    return binaryExpression;
}

void binaryExpressionPrint(BinaryExpression *binaryExpression, int level) {
    nodePrintTypeByLevel((POINTER) binaryExpression, level);
    printf("[operator=%s]", binaryExpression->operator);
    nodePrintByLevel(binaryExpression->left, level + 1);
    nodePrintByLevel(binaryExpression->right, level + 1);
}

void binaryExpressionDel(BinaryExpression *binaryExpression) {
    if (binaryExpression) {
        nodeDel(binaryExpression->left);
        nodeDel(binaryExpression->right);
        free(binaryExpression->operator);
        free(binaryExpression);
    }
}
