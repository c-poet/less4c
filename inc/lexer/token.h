#ifndef LESS4C_LEXER_H
#define LESS4C_LEXER_H

#include "inc/core/global.h"
#include "inc/core/chars_ref.h"

/// Token类型
typedef enum {
    /// 标识符
    TT_Identifier,
    /// 运算符
    TT_Operator,
    /// 逻辑运算符
    TT_Logic,
    /// 关键字
    TT_Keyword,
    /// 字面量
    TT_Literal,
    /// "{" or "}"
    TT_Brace,
    /// "(" or ")"
    TT_Bracket,
    /// ";"
    TT_Semicolon,
    // ":"
    TT_Colon,
    /// 结束符号
    TT_EOF,
} TokenType;

/// Token
typedef struct {
    /// 类型
    TokenType type;
    /// 位置信息
    struct {
        /// 当前偏移量
        int offset;
        /// 当前行
        int row;
        /// 当前列
        int col;
    } loc;
    /// 值
    char *value;
} Token;

/// 实例化Token
/// @param type 类型
/// @param value 值
/// @return Token
Token *tokenNew(TokenType type, char *value);

/// 实例化Token
/// @param type 类型
/// @param text 文本
/// @param start 开始下标
/// @param end 结束下标
Token *tokenNewByRange(TokenType type, const char *text, int start, int end);

/// 实例化Token
/// @param type 类型
/// @param c 值
/// @return Token
Token *tokenNewByChar(TokenType type, char c);

/// 实例化Token
/// @param type 类型
/// @param charsRef 值
/// @return Token
Token *tokenNewByCharsRef(TokenType type, CharsRef *charsRef);

/// 释放Token空间
/// @param token 地址
void tokenDel(Token *token);

/// Token类型转换成字符串
/// @param type Token Type
/// @return 转换结果
char *tokenTypeAsString(TokenType type);

#endif
