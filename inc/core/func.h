#ifndef LESS4C_CORE_FUNC_H
#define LESS4C_CORE_FUNC_H

#include "global.h"

/// 数字转字符数组
/// @param num 数字
/// @return 字符数组
char *intToChars(int num);

/// 字符串转double
/// @param chars 字符串
/// @param result 接收结果
/// @return 是否转换成功
BOOL charsToDouble(const char *chars, double *result);

/// 字符串转double
/// @param chars 字符串
/// @param start 开始下标
/// @param end 结束下标
/// @param result 接收结果
/// @return 是否转换成功
BOOL charsToDoubleByRange(const char *chars, int start, int end, double *result);

#endif
