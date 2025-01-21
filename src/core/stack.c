#include "inc/core/stack.h"
#include <malloc.h>

Stack *stackNew(int valueSize) {
    return stackNewByInit(0, valueSize);
}

Stack *stackNewByInit(int initSize, int valueSize) {
    if (initSize < 0 || valueSize <= 0) {
        return NULL;
    }
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }
    stack->size = 0;
    stack->actualSize = 0;
    stack->valueSize = valueSize;
    stack->values = NULL;
    if (initSize > 0) {
        stack->actualSize = initSize;
        stack->values = malloc(valueSize * stack->actualSize);
        if (!stack->values) {
            stackDel(stack);
            return NULL;
        }
    }
    return stack;
}

POINTER stackPop(Stack *stack) {
    return stack->size > 0 ? stack->values[--stack->size] : NULL;
}

POINTER stackPeek(Stack *stack) {
    return stack->size > 0 ? stack->values[stack->size - 1] : NULL;
}

BOOL stackPush(Stack *stack, POINTER val) {
    if (stack->values == NULL) {
        stack->actualSize = STACK_VALUES_R_LEN + 1;
        stack->values = malloc(stack->valueSize * stack->actualSize);
        if (!stack->values) {
            return BOOL_FALSE;
        }
    } else if (stack->size + 1 >= stack->actualSize) {
        stack->actualSize = STACK_VALUES_R_LEN + 1 + stack->size;
        POINTER*values = realloc(stack->values, stack->valueSize * stack->actualSize);
        if (!values) {
            return BOOL_FALSE;
        }
        stack->values = values;
    }
    stack->values[stack->size] = val;
    ++stack->size;
    return BOOL_TRUE;
}

BOOL stackEmpty(Stack *stack) {
    return stack->size <= 0;
}

void stackDel(Stack *stack) {
    if (stack) {
        free(stack->values);
        free(stack);
    }
}
