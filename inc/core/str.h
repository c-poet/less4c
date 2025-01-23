#ifndef LESS4C_CORE_STR_H
#define LESS4C_CORE_STR_H

#include "global.h"

#define CHARS_R_LEN 128

/// 动态Char数组
typedef struct {
    /// 当前长度
    int len;
    /// 实际分配长度
    int actualLen;
    /// 数组
    char *chars;
} String;

/// 实例化Chars
/// @return Chars
String *stringNew();

/// 实例批Chars并指定长度
/// @param len 长度
/// @return Chars
String *stringNewByLen(int len);

/// 拼接字符串
/// @param target 目标字符串
/// @param source 源字符串
/// @return 是否成功
BOOL stringAppend(String *target, String *source);

/// 拼接字符串
/// @param target 目标字符串
/// @param source 源字符串
/// @return 是否成功
BOOL stringAppendChars(String *target, const char *source);

/// 拼接字符串
/// @param target 目标字符串
/// @param c 字符
/// @return 是否成功
BOOL stringAppendChar(String *target, char c);

/// 拼接字符串
/// @param target 目标字符串
/// @param source 源字符串
/// @param start 开始位置
/// @param end 结束位置
/// @return 是否成功
BOOL stringAppendCharsRange(String *target, const char *source, int start, int end);

/// 拼接字符串
/// @param target 目标字符串
/// @param num 数字
/// @return 是否成功
BOOL stringAppendInt(String *target, int num);

/// 释放字符串内存
/// @param string 字符串
void stringDel(String *string);

#endif
