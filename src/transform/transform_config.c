#include "inc/transform/transform_config.h"
#include <malloc.h>

TransformConfig *transformConfigNew() {
    TransformConfig *config = malloc(sizeof(TransformConfig));
    if (!config) {
        return NULL;
    }
    return config;
}

void transformConfigDel(TransformConfig *config) {
    if (config) {
        free(config);
    }
}
