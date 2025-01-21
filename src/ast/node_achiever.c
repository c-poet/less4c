#include "inc/ast/node_achiever.h"
#include <malloc.h>
#include <stdio.h>

VarDeclare *varDeclareNew(const char *name) {
    VarDeclare *varDeclare = malloc(sizeof(VarDeclare));
    if (!varDeclare) {
        return NULL;
    }
    varDeclare->name = name;
    return varDeclare;
}

void varDeclareDel(VarDeclare *varDeclare) {
    free(varDeclare);
}

void varDeclarePrint(VarDeclare *varDeclare, int level) {
    printf("[name=%s]\n", varDeclare->name);
}

Node *nodeVarDeclareNew(const char *name) {
    VarDeclare *varDeclare = varDeclareNew(name);
    if (varDeclare == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_VarDeclare, varDeclare);
    if (node == NULL) {
        varDeclareDel(varDeclare);
        return NULL;
    }
    node->print = (POINTER) varDeclarePrint;
    node->destroy = (POINTER) varDeclareDel;
    return node;
}

CallVariable *callVariableNew(const char *name, const Node *var) {
    CallVariable *callDeclare = malloc(sizeof(CallVariable));
    if (!callDeclare) {
        return NULL;
    }
    callDeclare->name = name;
    callDeclare->var = var;
    return callDeclare;
}

void callVariableDel(CallVariable *callVariable) {
    free(callVariable);
}

void callVariablePrint(CallVariable *callVariable, int level) {
    printf("[name=%s]\n", callVariable->name);
    nodePrintByLevel(callVariable->var, level + 1);
}

Node *nodeCallVariableNew(const char *name, const Node *var) {
    CallVariable *callDeclare = callVariableNew(name, var);
    if (callDeclare == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_CallVariable, callDeclare);
    if (node == NULL) {
        callVariableDel(callDeclare);
        return NULL;
    }
    node->print = (POINTER) callVariablePrint;
    node->destroy = (POINTER) callVariableDel;
    return node;
}

NumberLiteral *numberLiteralNew(const char *val, double number, const char *unit) {
    NumberLiteral *numberLiteral = malloc(sizeof(NumberLiteral));
    if (!numberLiteral) {
        return NULL;
    }
    numberLiteral->value = val;
    numberLiteral->number = number;
    numberLiteral->unit = unit;
    return numberLiteral;
}

void numberLiteralDel(NumberLiteral *numberLiteral) {
    free(numberLiteral);
}

void numberLiteralPrint(NumberLiteral *numberLiteral, int level) {
    printf("[value=%s,number=%f,unit=%s]\n", numberLiteral->value, numberLiteral->number, numberLiteral->unit);
}

Node *nodeNumberLiteralNew(const char *val, double number, const char *unit) {
    NumberLiteral *numberLiteral = numberLiteralNew(val, number, unit);
    if (numberLiteral == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_NumberLiteral, numberLiteral);
    if (node == NULL) {
        numberLiteralDel(numberLiteral);
        return NULL;
    }
    node->print = (POINTER) numberLiteralPrint;
    node->destroy = (POINTER) numberLiteralDel;
    return node;
}

StringLiteral *stringLiteralNew(const char *val) {
    StringLiteral *stringLiteral = malloc(sizeof(StringLiteral));
    if (!stringLiteral) {
        return NULL;
    }
    stringLiteral->value = val;
    return stringLiteral;
}

void stringLiteralDel(StringLiteral *stringLiteral) {
    free(stringLiteral);
}

void stringLiteralPrint(StringLiteral *stringLiteral, int level) {
    printf("[value=%s]\n", stringLiteral->value);
}

Node *nodeStringLiteralNew(const char *val) {
    StringLiteral *stringLiteral = stringLiteralNew(val);
    if (stringLiteral == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_StringLiteral, stringLiteral);
    if (node == NULL) {
        stringLiteralDel(stringLiteral);
        return NULL;
    }
    node->print = (POINTER) stringLiteralPrint;
    node->destroy = (POINTER) stringLiteralDel;
    return node;
}

BinaryExpression *binaryExpressionNew(const char *op, const Node *left, const Node *right) {
    BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
    if (!binaryExpression) {
        return NULL;
    }
    binaryExpression->operator = op;
    binaryExpression->left = left;
    binaryExpression->right = right;
    return binaryExpression;
}

void binaryExpressionDel(BinaryExpression *binaryExpression) {
    if (binaryExpression) {
        free(binaryExpression);
    }
}

void binaryExpressionPrint(BinaryExpression *binaryExpression, int level) {
    printf("[operator=%s]\n", binaryExpression->operator);
    nodePrintByLevel(binaryExpression->left, level + 1);
    nodePrintByLevel(binaryExpression->right, level + 1);
}

Node *nodeBinaryExpressionNew(const char *op, const Node *left, const Node *right) {
    BinaryExpression *binaryExpression = binaryExpressionNew(op, left, right);
    if (binaryExpression == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_BinaryExpression, binaryExpression);
    if (node == NULL) {
        binaryExpressionDel(binaryExpression);
        return NULL;
    }
    node->print = (POINTER) binaryExpressionPrint;
    node->destroy = (POINTER) binaryExpressionDel;
    return node;
}
