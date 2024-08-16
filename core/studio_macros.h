
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



#ifndef PI
#define PI (3.1415926535897932384626433832795028841971693993751f)
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
#endif

#ifndef AO_INFO_PRINT
// 打印提示信息
#define AO_INFO_PRINT(s, ...) printf(AO_PRINTF_COLOR_CYAN "\n[INFO] %s:%I32d \n " s AO_PRINTF_COLOR_NONE " \n", AO_FILE_NAME, __LINE__, ##__VA_ARGS__);
#endif

#ifndef AO_ERROR_PRINT
// 打印错误信息
#define AO_ERROR_PRINT(s, ...) printf(AO_PRINTF_COLOR_RED "\n[ERROR] %s:%I32d \n ... " s AO_PRINTF_COLOR_NONE, AO_FILE_NAME, __LINE__, ##__VA_ARGS__);
#endif





#endif  // STUDIO_MACROS_H
