#ifndef LESS4C_AST_PARSE_FUNC_PRIVATE_H
#define LESS4C_AST_PARSE_FUNC_PRIVATE_H

#include "parse_context.h"
#include "inc/core/list.h"
#include "inc/lexer/scan_result.h"

/// 查询上下文中变量定义的节点
/// @param context 上下文
/// @param name 变量名
/// @return 节点
Node *findVariable(ParseContext *context, const char *name);

/// 判断当前token是否是在块开始之前
/// @param context 上下文
/// @return 是否在块开始之前
BOOL isRulePrelude(ParseContext *context);

/// 去除字符串左右两边的引号
/// @param str 字符串
/// @return 去除结果
char *removeQuote(char *str);

/// 读取文件
/// @param config 配置
/// @param fileName 文件名
char *defaultReadFile(ParseConfig *config, char *fileName);

/// 扫描Token
/// @param config 配置
/// @param content 内容
/// @return 扫描结果
ScanResult *defaultScanToken(ParseConfig *config, char *content);

/// 调用解析并获取根节点
/// @param context 上下文
/// @param fileName 文件名
Node *invokeParseGetRootNode(ParseContext *context, char *fileName);

#endif
