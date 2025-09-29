#include "logger.h"
#include <stdarg.h>  // 用于处理可变参数
#include <time.h>    // 可选：添加时间戳

// 全局变量：记录最小输出级别（低于此级别的日志不打印）
static LogLevel g_min_level = LOG_LEVEL_DEBUG;

// 初始化日志：设置最小输出级别
void log_init(LogLevel min_level) {
    g_min_level = min_level;
}

// 辅助函数：获取级别对应的字符串（如 "DEBUG"、"ERROR"）
static const char* get_level_str(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_WARN:  return "WARN";
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

// 通用日志输出函数（内部实现，处理级别过滤和格式化）
static void log_output(LogLevel level, const char* format, va_list args) {
    // 级别过滤：如果当前级别低于最小级别，不输出
    if (level < g_min_level) {
        return;
    }

    // 可选：添加时间戳（简单实现）
    time_t now = time(nullptr);
    struct tm* tm_info = localtime(&now);
    char time_buf[20] = {0};
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);

    // 打印前缀（时间 + 级别）
    printf("[%s] [%s] ", time_buf, get_level_str(level));

    // 打印用户日志内容（格式化可变参数）
    vprintf(format, args);

    // 换行（避免日志内容挤在一起）
    printf("\n");
}

// 各级别日志的具体实现（调用通用输出函数）
void log_debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_output(LOG_LEVEL_DEBUG, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_output(LOG_LEVEL_INFO, format, args);
    va_end(args);
}

void log_warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_output(LOG_LEVEL_WARN, format, args);
    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_output(LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void log_fatal(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_output(LOG_LEVEL_FATAL, format, args);
    va_end(args);
}
