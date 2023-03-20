//
// Created by Huawei on 20.03.2023.
//

#ifndef FRONTENDTENSORFLOW_HELP_FUN_H
#define FRONTENDTENSORFLOW_HELP_FUN_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


int metrics(const int16_t* data, int size, char name[]);
#ifdef __cplusplus
}  // extern "C"
#endif

#endif //FRONTENDTENSORFLOW_HELP_FUN_H
