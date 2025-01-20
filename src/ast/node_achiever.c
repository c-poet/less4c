#include "inc/ast/node_achiever.h"
#include <malloc.h>

VarDeclare *varDeclareNew(char *name) {
    VarDeclare *varDeclare = malloc(sizeof(VarDeclare));
    if (!varDeclare) {
        return NULL;
    }
    varDeclare->name = name;
    return varDeclare;
}

NumberLiteral *numberLiteralNew(char *val) {
    NumberLiteral *numberLiteral = malloc(sizeof(NumberLiteral));
    if (!numberLiteral) {
        return NULL;
    }
    numberLiteral->value = val;
    return numberLiteral;
}
