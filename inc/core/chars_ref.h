#ifndef LESS4C_CORE_CHARS_REF_H
#define LESS4C_CORE_CHARS_REF_H

#include "global.h"

/// Char软链接
typedef struct {
    /// 开始索引
    int start;
    /// 结束索引
    int end;
    /// Char数组
    const char *chars;
} CharsRef;

/// 实例化char数组软链接
/// @param chars 参照内容
/// @param start 开始索引
/// @param
CharsRef *charsRefNew(const char *chars, int start, int end);

/// 移动开始指针
/// @param charsRef char数组软链接
/// @param index 数量
void charsRefMoveStartIndex(CharsRef *charsRef, int index);

/// 移动结束指针
/// @param charsRef char数组软链接
/// @param index 数量
void charsRefMoveEndIndex(CharsRef *charsRef, int index);

/// 比较两个char数组
/// @param charsRef1 数组1
/// @param charsRef2 数组2
/// @return 是否相等
BOOL charsRefEquals(CharsRef *charsRef1, CharsRef *charsRef2);

/// 比较两个char数组
/// @param charsRef1 数组1
/// @param chars 数组2
/// @return 是否相等
BOOL charsRefEqualsChars(CharsRef *charsRef, const char *chars);

/// 转换成char数组
/// @param charsRef chars数组软链接
/// @return char数组
char *charsRefToChars(CharsRef *charsRef);

/// 删除char数组软连接
/// @param charsRef char数组软连接
void charsRefDel(CharsRef *charsRef);

#endif
