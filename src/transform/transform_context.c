#include "inc/transform/transform_context.h"
#include "inc/core/func.h"
#include <malloc.h>

TransformContext *transformContextNew(TransformConfig *config, Ast *targetAst, Ast *sourceAst) {
    TransformContext *context = malloc(sizeof(TransformContext));
    if (!context) {
        return NULL;
    }
    context->parent = NULL;
    context->targetAst = targetAst;
    context->sourceAst = sourceAst;
    context->targetNode = targetAst->root;
    context->sourceNode = sourceAst->root;
    context->config = config;
    context->varTable = mapNew((POINTER) charsEq, (POINTER) charsHashCode);
    if (!context->varTable) {
        transformContextDel(context);
        return NULL;
    }
    return context;
}

void transformContextDel(TransformContext *context) {
    if (context) {
        free(context);
    }
}
