//
// Created by a00874817 on 16/06/2024.
//
#include "Log/Log.h"

#include <stdio.h>
#include <stdarg.h>

void Log::info(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs, pMessage);
    printf("LOG_INFO : ogl-model-loader : ");
    vprintf(pMessage, varArgs);
    printf("\n");

    va_end(varArgs);
}

void Log::error(const char *pMessage, ...) {
    va_list varArgs;
    va_start(varArgs, pMessage);

    printf("LOG_ERROR : ogl-model-loader : ");
    vprintf(pMessage, varArgs);
    printf("\n");

    va_end(varArgs);
}

void Log::warn(const char* pMessage, ...) {
    va_list varArgs;
    va_start(varArgs, pMessage);

    printf("LOG_WARN : ogl-model-loader : ");
    vprintf(pMessage, varArgs);
    printf("\n");

    va_end(varArgs);
}

void Log::debug(const char* pMessage, ...) {
    va_list varArgs;
    va_start(varArgs, pMessage);

    printf("LOG_DEBUG : ogl-model-loader : ");
    vprintf(pMessage, varArgs);
    printf("\n");

    va_end(varArgs);
}