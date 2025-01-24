#ifndef LESS4C_TRANSFORM_CONFIG_H
#define LESS4C_TRANSFORM_CONFIG_H

#include "inc/core/global.h"

/// 转换配置
typedef struct {

} TransformConfig;

/// 创建转换配置
/// @return 转换配置
TransformConfig *transformConfigNew();

/// 释放转换配置
/// @param config 配置
void transformConfigDel(TransformConfig *config);

#endif
