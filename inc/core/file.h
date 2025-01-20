#ifndef LESS4C_CORE_FILE_H
#define LESS4C_CORE_FILE_H

#include "str.h"

/// 读取文件所有内容
/// @param fileName 文件名
/// @return 文件内容，失败返回NULL
String *fileReadAll(char *fileName);

#endif
