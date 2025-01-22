#include "inc/ast/node/number_literal.h"
#include <malloc.h>
#include <stdio.h>

NumberLiteral *numberLiteralNew(const char *val, double number, const char *unit) {
    NumberLiteral *numberLiteral = malloc(sizeof(NumberLiteral));
    if (!numberLiteral) {
        return NULL;
    }
    nodeInit((POINTER) numberLiteral);
    numberLiteral->type = NT_NumberLiteral;
    numberLiteral->value = val;
    numberLiteral->number = number;
    numberLiteral->unit = unit;
    numberLiteral->print = (POINTER) numberLiteralPrint;
    numberLiteral->destroy = (POINTER) numberLiteralDel;
    return numberLiteral;
}

void numberLiteralPrint(NumberLiteral *numberLiteral, int level) {
    nodePrintTypeByLevel((POINTER) numberLiteral, level);
    printf("[value=%s,number=%f,unit=%s]", numberLiteral->value, numberLiteral->number, numberLiteral->unit);
}

void numberLiteralDel(NumberLiteral *numberLiteral) {
    if (numberLiteral) {
        free(numberLiteral);
    }
}
