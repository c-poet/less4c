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

/// 创建列表
/// @param valueSize 列表值大小
/// @return 列表
List *listNew(int valueSize);

/// 创建列表
/// @param initSize 初始化大小
/// @param valueSize 列表值大小
/// @return 列表
List *listNewByInit(int initSize, int valueSize);

/// 列表添加值
/// @param list 列表
/// @param val 值
/// @return 是否添加成功
BOOL listAdd(List *list, POINTER val);

/// 列表插入值
/// @param list 列表
/// @param index 插入的索引
/// @param val 值
/// @return 是否添加成功
BOOL listInsert(List *list, int index, POINTER val);

/// 列表移出值
/// @param list 列表
/// @param val 需要移出的值
/// @return 是否成功
BOOL listRemove(List *list, POINTER val);

/// 列表移出最后一个值
/// @param list 列表
POINTER listRemoveLast(List *list);

/// 列表根据索引移出值
/// @param list 列表
/// @param index 移出值索引
/// @return 移出值地址
POINTER listRemoveByIndex(List *list, int index);

/// 判断列表是否为空
/// @param list 列表
/// @return 是否为空
BOOL listEmpty(List *list);

/// 遍历列表项
/// @param list 列表
/// @param func 遍历函数
void listEach(List *list, void func(POINTER val));

/// 释放列表
/// @param list 列表
void listDel(List *list);

#endif
