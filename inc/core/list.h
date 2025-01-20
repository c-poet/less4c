#ifndef LESS4C_CORE_LIST_H
#define LESS4C_CORE_LIST_H

#include "global.h"

#define LIST_VALUES_R_LEN 10

/// 列表
typedef struct {
    /// 列表大小
    int size;
    /// 实际分发的数据大小
    int actualSize;
    /// 单位数据大小
    int valueSize;
    /// 数据列表
    POINTER*values;
} List;

List *listNew(int valueSize);

List *listNewByInit(int initSize, int valueSize);

BOOL listAdd(List *list, POINTER val);

BOOL listInsert(List *list, int index, POINTER val);

BOOL listRemove(List *list, POINTER val);

POINTER listRemoveByIndex(List *list, int index);

void listEach(List *list, void func(POINTER val));

void listDel(List *list);

#endif
