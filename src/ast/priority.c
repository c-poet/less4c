#include "inc/ast/priority.h"

int operatorPriority(const char *op) {
    switch (op[0]) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}
