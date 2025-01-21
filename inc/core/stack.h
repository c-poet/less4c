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

/// 实例化栈
/// @param valueSize 元素大小
Stack *stackNew(int valueSize);

/// 实例化栈
/// @param initSize 初始化大小
/// @param valueSize 元素大小
Stack *stackNewByInit(int initSize, int valueSize);

/// 元素出栈
/// @param stack 栈
/// @return 元素
POINTER stackPop(Stack *stack);

/// 查看栈顶元素
/// @param stack 栈
/// @return 元素
POINTER stackPeek(Stack *stack);

/// 添加元素
/// @param stack 栈
/// @param val 元素
/// @return 是否添加成功
BOOL stackPush(Stack *stack, POINTER val);

/// 判断栈是否为空
/// @param stack 栈
/// @return 是否为空
BOOL stackEmpty(Stack *stack);

/// 销毁栈
/// @param stack 栈
void stackDel(Stack *stack);

#endif
