#pragma once
#ifndef STUDIO_MACROS_H
#define STUDIO_MACROS_H

// 标准c++头文件
// 输入输出库
#include <iostream>
#include <sstream>
// 字符串库
#include <string>
// 容器
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <stack>
#include <deque>
// 算法
#include <algorithm>
// 数值
#include <cmath>
// 输入输出
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <ctime>
// 文件和流库
#include <fstream>
#include <filesystem>
// 多线程库
#include <thread>
#include <mutex>
#include <future>
#include <atomic>
#include <functional>
// 正则表达式
#include <regex>
#include <climits>  // 包含 INT_MAX 定义

#include <locale>
#include <codecvt> // 注意：在一些编译器中可能需要这个头文件来使用 codecvt_utf8

// π
#ifndef PI
#define PI (3.1415926535897932384626433832795028841971693993751f)
#endif

// π
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// π/2
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

// 自然指数e
#ifndef BASE_E
#define BASE_E 2.71828182845904523536
#endif

// 最小浮点数
#ifndef TINY
#define TINY (1e-18)
#endif

// 一个极小的浮点数, 用于浮点数比较		EPS 与opencv的冲突
#ifndef AO_EPSILON
#define AO_EPSILON (.1e-18)
#endif

#ifndef AO_MAX
#define AO_MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef AO_MIN
#define AO_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// 转化小端序的int值
#define AO_CONVERT_LITTLE_ENDIAN_LONG(src_ptr) (src_ptr[3] << 24 | (src_ptr[2] << 16) | src_ptr[1] << 8 | src_ptr[0])
// 转化小端序的int值
#define AO_CONVERT_LITTLE_ENDIAN_INT(src_ptr) (src_ptr[3] << 24 | (src_ptr[2] << 16) | src_ptr[1] << 8 | src_ptr[0])
// 转化小端序的short值
#define AO_CONVERT_LITTLE_ENDIAN_SHORT(src_ptr) (src_ptr[1] << 8) + src_ptr[0]

#ifndef AO_FILE_NAME
// 获取当前文件名称
#if IS_WIN32
#define AO_FILE_NAME (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)
#else
#define AO_FILE_NAME (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#endif
#endif

#define AO_PRINTF_COLOR_NONE "\033[m"
#define AO_PRINTF_COLOR_RED "\033[0;32;31m"
#define AO_PRINTF_COLOR_LIGHT_RED "\033[1;31m"
#define AO_PRINTF_COLOR_GREEN "\033[0;32;32m"
#define AO_PRINTF_COLOR_LIGHT_GREEN "\033[1;32m"
#define AO_PRINTF_COLOR_BLUE "\033[0;32;34m"
#define AO_PRINTF_COLOR_LIGHT_BLUE "\033[1;34m"
#define AO_PRINTF_COLOR_DARK_GRAY "\033[1;30m"
#define AO_PRINTF_COLOR_CYAN "\033[0;36m"
#define AO_PRINTF_COLOR_LIGHT_CYAN "\033[1;36m"
#define AO_PRINTF_COLOR_PURPLE "\033[0;35m"
#define AO_PRINTF_COLOR_LIGHT_PURPLE "\033[1;35m"
#define AO_PRINTF_COLOR_BROWN "\033[0;33m"
#define AO_PRINTF_COLOR_YELLOW "\033[1;33m"
#define AO_PRINTF_COLOR_LIGHT_GRAY "\033[0;37m"
#define AO_PRINTF_COLOR_WHITE "\033[1;37m"

#ifndef AO_PRINTF
// 打印信息 未封装
#define AO_PRINTF(s, ...)
#endif // AO_PRINTF

#ifndef AO_INFO_PRINT
// 打印提示信息
#define AO_INFO_PRINT(s, ...) printf(AO_PRINTF_COLOR_CYAN "\n[INFO] %s:%I32d \n " s AO_PRINTF_COLOR_NONE " \n", AO_FILE_NAME, __LINE__, ##__VA_ARGS__);
#endif // AO_INFO_PRINT

#ifndef AO_ERROR_PRINT
// 打印错误信息
#define AO_ERROR_PRINT(s, ...) printf(AO_PRINTF_COLOR_RED "\n[ERROR] %s:%I32d \n ... " s AO_PRINTF_COLOR_NONE, AO_FILE_NAME, __LINE__, ##__VA_ARGS__);
#endif // AO_ERROR_PRINT

#ifndef AO_TIME
#define AO_TIME
#define SEC_IN_MIN 60
#define MIN_IN_HOUR 60
#define HOUR_IN_DAY 24
#define SEC_IN_HOUR (SEC_IN_MIN * MIN_IN_HOUR)
#define MIN_IN_DAY (MIN_IN_HOUR * HOUR_IN_DAY)
#define SEC_IN_DAY (SEC_IN_MIN * MIN_IN_HOUR * HOUR_IN_DAY)
#endif // AO_TIME

#ifndef AO_KB
#define AO_KB (1024)
#define AO_MB (1024 * 1024)
#define AO_GB (1024 * 1024 * 1024)
#endif


#endif  // STUDIO_MACROS_H
