#include "inc/transform/transform.h"
#include "inc/transform/transform_context.h"

Ast *transformToCssAst(TransformConfig *config, Ast *lessAst) {
    Ast *ast = astNew();
    TransformContext *context = transformContextNew(config, ast, lessAst);
    if (context == NULL) {
        astDel(ast);
        return NULL;
    }
    return ast;
}


