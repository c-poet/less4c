#include "inc/ast/priority.h"
#include "inc/lexer/token_const.h"

int operatorPriority(const char *op) {
    switch (op[0]) {
        case TOKEN_GT:
        case TOKEN_LT:
        case TOKEN_EQ:
            return 10;
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return 15;
        case TOKEN_RIDE:
        case TOKEN_DIVISION:
        case TOKEN_REA:
            return 20;
        default:
            return 0;
    }
}
