#ifndef LESS4C_CORE_STACK_H
#define LESS4C_CORE_STACK_H

#include "global.h"

#define STACK_VALUES_R_LEN 5

/// 栈
typedef struct {
    /// 列表大小
    int size;
    /// 实际分发的数据大小
    int actualSize;
    /// 单位数据大小
    int valueSize;
    /// 数据列表
    POINTER*values;
} Stack;

Stack *stackNew(int valueSize);

Stack *stackNewByInit(int initSize, int valueSize);

POINTER stackPop(Stack *stack);

POINTER stackPeek(Stack *stack);

BOOL stackPush(Stack *stack, POINTER val);

BOOL stackEmpty(Stack *stack);

void stackDel(Stack *stack);

#endif
