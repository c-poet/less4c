#include "inc/ast/parse_func_private.h"
#include "inc/ast/node/var_declare.h"
#include "inc/lexer/token_const.h"
#include "inc/core/func.h"

Node *findVariable(ParseContext *context, const char *name) {
    List *children;
    Node *node = context->root;
    while (node != NULL) {
        if ((children = nodeGetChildren(node)) != NULL) {
            for (int i = 0; i < children->size; ++i) {
                if (((Node *) children->values[i])->type == NT_VarDeclare
                    && charsEq(((VarDeclare *) children->values[i])->name, name)) {
                    return children->values[i];
                }
            }
        }
        node = node->parent;
    }
    return NULL;
}

BOOL isRulePrelude(ParseContext *context) {
    Token *token;
    int i = context->cur;
    while ((token = context->tokens[i])->type != TT_EOF && token->type != TT_Brace) {
        ++i;
    }
    return token->type == TT_Brace && charsEqChar(token->value, TOKEN_LBRACE);
}
