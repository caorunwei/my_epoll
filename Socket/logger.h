#pragma once
#include <cstdio>  // 用于格式化字符串

// 日志级别枚举（从低到高，便于过滤）
enum LogLevel {
    LOG_LEVEL_DEBUG,   // 调试信息（开发阶段用）
    LOG_LEVEL_INFO,    // 普通信息（正常运行状态）
    LOG_LEVEL_WARN,    // 警告（不影响主流程，但需注意）
    LOG_LEVEL_ERROR,   // 错误（功能受影响，需处理）
    LOG_LEVEL_FATAL    // 致命错误（程序可能崩溃）
};

// 初始化日志（可选：后续可扩展为设置输出文件、级别等）
// 初期实现可以为空，或仅设置是否输出调试日志
void log_init(LogLevel min_level = LOG_LEVEL_DEBUG);

// 按级别输出日志（支持printf风格的格式化字符串）
// 参数：格式化字符串 + 可变参数（与printf一致）
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);
void log_fatal(const char* format, ...);