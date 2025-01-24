#ifndef LESS4C_CORE_MAP_H
#define LESS4C_CORE_MAP_H

#include "global.h"

/// Map项
typedef struct S_MapItem {
    /// Hash值
    UINT hashCode;
    /// 键
    POINTER k;
    /// 值
    POINTER v;
    /// 下一个节点
    struct S_MapItem *next;
} MapItem;

typedef struct {
    /// 大小
    int size;
    /// 已分配的table大小
    int tableSize;
    /// Table
    MapItem **table;
    /// 判断两个键是否相等
    BOOL (*equals)(POINTER, POINTER);
    /// 计算键的HashCode
    UINT (*hashCode)(POINTER);
} Map;

/// 初始化Map
/// @param equals 键比较函数
/// @param hashCode 键hash求值函数
/// @return map
Map *mapNew(BOOL (*equals)(POINTER, POINTER), UINT (*hashCode)(POINTER));

/// 初始化map
/// @param initSize 初始化大小
/// @param equals 键比较函数
/// @param hashCode 键hash求值函数
/// @return map
Map *mapNewByInit(int initSize, BOOL (*equals)(POINTER, POINTER), UINT (*hashCode)(POINTER));

/// 获取值
/// @param map Map
/// @param k 键
POINTER mapGet(Map *map, POINTER k);

/// 添加值
/// @param map Map
/// @param k 键
/// @param v 值
BOOL mapPut(Map *map, POINTER k, POINTER v);

/// 移出值
/// @param map Map
/// @param k 键
/// @return 值
POINTER mapRemove(Map *map, POINTER k);

/// 遍历k-v
/// @param map Map
/// @param func 遍历函数
void mapEach(Map *map, void (*func)(POINTER, POINTER));

/// 释放Map
/// @param Map
void mapDel(Map *map);

#endif
