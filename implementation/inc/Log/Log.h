//
// Created by a00874817 on 16/06/2024.
//

#ifndef OGL_MODEL_LOADER_LOG_H
#define OGL_MODEL_LOADER_LOG_H

class Log{
public:
    static void error(const char* pMessage, ...);
    static void warn(const char* pMessage, ...);
    static void info(const char* pMessage, ...);
    static void debug(const char* pMessage, ...);
#ifndef NDEBUG
#define As_uB_Log_debug(...) Log::Debug(__VA_ARGS__)
#else
#define As_uB_Log_debug(...)
#endif
};

#endif //OGL_MODEL_LOADER_LOG_H
