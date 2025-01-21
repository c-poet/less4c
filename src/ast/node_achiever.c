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

void varDeclarePrint(VarDeclare *varDeclare) {
    printf("name=%s", varDeclare->name);
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

void callVariablePrint(CallVariable *callVariable) {
    printf("name=%s => ", callVariable->name);
    callVariable->var->print(callVariable->var->achiever);
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

void numberLiteralPrint(NumberLiteral *numberLiteral) {
    printf("value=%s,number=%f,unit=%s", numberLiteral->value, numberLiteral->number, numberLiteral->unit);
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

void stringLiteralPrint(StringLiteral *stringLiteral) {
    printf("value=%s", stringLiteral->value);
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

BinaryExpression *binaryExpressionNew(const char *op) {
    BinaryExpression *binaryExpression = malloc(sizeof(BinaryExpression));
    if (!binaryExpression) {
        return NULL;
    }
    binaryExpression->operator = op;
    return binaryExpression;
}

void binaryExpressionDel(BinaryExpression *binaryExpression) {
    if (binaryExpression) {
        free(binaryExpression);
    }
}

void binaryExpressionPrint(BinaryExpression *binaryExpression) {
    printf("operator=%s", binaryExpression->operator);
}

Node *nodeBinaryExpressionNew(const char *op, Node *left, Node *right) {
    BinaryExpression *binaryExpression = binaryExpressionNew(op);
    if (binaryExpression == NULL) {
        return NULL;
    }
    Node *node = nodeNew(NT_BINARY_EXPRESSION, binaryExpression);
    if (node == NULL) {
        binaryExpressionDel(binaryExpression);
        return NULL;
    }
    node->print = (POINTER) binaryExpressionPrint;
    node->destroy = (POINTER) binaryExpressionDel;
    nodeAddChild(node, left);
    nodeAddChild(node, right);
    return node;
}
