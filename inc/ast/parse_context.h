#ifndef LESS4C_AST_PARSE_CONTEXT_H
#define LESS4C_AST_PARSE_CONTEXT_H

#include "ast.h"
#include "inc/lexer/token.h"

/// 解析上下文
typedef struct {
    /// 当前Token的下标
    int cur;
    /// Token序列
    Token **tokens;
    /// 当前上下文根节点
    Node *root;
    /// 解析信息
    char *message;
    /// 正在构建的语法树
    Ast *ast;
} ParseContext;

/// 创建解析上下文
/// @return 上下文
ParseContext *parseContextNew(Token **tokens);

/// 判断是否继续
/// @param context 上下文
/// @return 是否还有Token序列
BOOL parseContextHasNext(ParseContext *context);

/// 查看上一个token序列
/// @param context 上下文
/// @return Token
Token *parseContextPeekPre(ParseContext *context);

/// 获取下一个Token序列
/// @param context 上下文
/// @return Token
Token *parseContextNext(ParseContext *context);

/// 查看下一个Token序列
/// @param context 上下文
/// @return Token
Token *parseContextPeekNext(ParseContext *context);

/// 设置错误信息
/// @param context 上下文
/// @param message 信息
void parseContextMessage(ParseContext *context, char *message);

/// 释放解释上下文
/// @param context 上下文
void parseContextDel(ParseContext *context);

#endif
