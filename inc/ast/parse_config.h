#ifndef LESS4C_AST_PARSE_CONFIG_H
#define LESS4C_AST_PARSE_CONFIG_H

#include "inc/core/global.h"
#include "inc/lexer/scan_result.h"

/// 解析处理器
typedef void (*ParseHandler)(POINTER);

/// 解析配置
typedef struct S_ParseConfig {
    /// 文件所在路径（相对查找时使用）
    char *filePath;
    /// 文件后缀名
    char *fileSuffix;
    /// 开始解析
    ParseHandler startParse;
    /// 解析Identifier
    ParseHandler parseIdentifier;
    /// 解析字面量
    ParseHandler parseLiteral;
    /// 解析块
    ParseHandler parseBrace;
    /// 解析表达式
    ParseHandler parseExpression;
    /// 解析关键字
    ParseHandler parseKeyword;
    /// 解析导入
    ParseHandler parseImport;
    /// 结束解析
    ParseHandler endParse;

    /// 读取文件
    char *(*readFile)(struct S_ParseConfig *, char *);

    /// 扫描文件获取Token
    ScanResult *(*scanToken)(struct S_ParseConfig *, char *);
} ParseConfig;

/// 创建解析配置
/// @return 解析配置
ParseConfig *parseConfigNew();

/// 解析配置初始化
/// @param config 解析配置
void parseConfigInit(ParseConfig *config);

/// 释放解析配置
/// @param config 解析配置
void parseConfigDel(ParseConfig *config);

#endif
