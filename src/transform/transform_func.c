#include "inc/transform/transform_func.h"

void startTransform(TransformContext *context) {
    switch (context->sourceNode->type) {
        case NT_BinaryExpression:
        default:
            break;
    }
}

void endTransform(TransformContext *context) {
}
