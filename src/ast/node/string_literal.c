#include "inc/ast/node/string_literal.h"
#include <stdio.h>
#include <malloc.h>

StringLiteral *stringLiteralNew(const char *val) {
    StringLiteral *stringLiteral = malloc(sizeof(StringLiteral));
    if (!stringLiteral) {
        return NULL;
    }
    nodeInit((POINTER) stringLiteral);
    stringLiteral->type = NT_StringLiteral;
    stringLiteral->value = val;
    stringLiteral->print = (POINTER) stringLiteralPrint;
    stringLiteral->destroy = (POINTER) stringLiteralDel;
    return stringLiteral;
}

void stringLiteralPrint(StringLiteral *stringLiteral, int level) {
    nodePrintTypeByLevel((POINTER) stringLiteral, level);
    printf("[value=%s]", stringLiteral->value);
}

void stringLiteralDel(StringLiteral *stringLiteral) {
    if (stringLiteral) {
        free(stringLiteral);
    }
}
