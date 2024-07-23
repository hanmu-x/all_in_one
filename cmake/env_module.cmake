# 设置CMake的最小要求版本为3.15
cmake_minimum_required(VERSION 3.15)

# 包含用于检查C++头文件存在的模块
include(CheckIncludeFileCXX)

# 允许在 foreach 循环中使用松散的语法结构
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

# 设置CMake生成的Makefile中的详细信息级别
set(CMAKE_VERBOSE_MAKEFILE ON)

# 自动包含当前目录下的头文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 如果没有设置构建类型，则自动设为Debug
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
    message("AUTO SET CMAKE_BUILD_TYPE : Debug")
endif()

# 输出系统信息
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "This is Linux")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Android")
    message(STATUS "This is Android")
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "This is Windows")
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    message(STATUS "this is aarch64 cpu")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    message(STATUS "this is x86_64 cpu")
endif()

# 检测目标平台的位数
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_NAME "x64")
    message(STATUS "Target is 64 bits")
else ()
    set(ARCH_NAME "x32")
    message(STATUS "Target is 32 bits")
endif ()

# 检查并设置C++标准
foreach(feature ${CMAKE_CXX_COMPILE_FEATURES})
    if("${feature}" STREQUAL "cxx_std_11")
        add_definitions(-DSU_SUPPORT_CXX11=1)
        set(SU_SUPPORT_CXX11 TRUE)
    elseif("${feature}" STREQUAL "cxx_std_17")
        add_definitions(-DSU_SUPPORT_CXX17=1)
        set(SU_SUPPORT_CXX17 TRUE)
    elseif("${feature}" STREQUAL "cxx_std_20")
        # 未启用C++20
    endif()
endforeach()

# 根据支持的C++标准设置CMake
if(SU_SUPPORT_CXX20)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    add_definitions(-D_HAS_STD_BYTE=0)
    message("使用C++20标准")
elseif(SU_SUPPORT_CXX17)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    add_definitions(-D_HAS_STD_BYTE=0)
    message("使用C++17标准")
elseif(SU_SUPPORT_CXX11)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    message("使用C++11标准")
endif()

# 添加预处理器定义
add_definitions(-DENABLE_SILLY_LOG)
add_definitions(-DNOMINMAX)
add_definitions(-DUNICODE)

# 根据操作系统设置特定的编译选项和库
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(IS_LINUX TRUE)
    set(PLATFORM_NAME "Linux")
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread -fPIC -Wall -fopenmp -Wunused-function -Wunused-variable")
    set(STATIC_LIB_SUFFIX "a")
    set(DYNAMIC_LIB_SUFFIX "so")
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(PLATFORM_NAME "Windows")
    set(IS_WINDOWS TRUE)
    add_definitions(-DTFF_INLINE_SPECIFIER=inline)
    add_definitions(-DIS_WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_compile_options(/wd4819 /wd4005 /wd4834 /utf-8 /openmp)
    set(STATIC_LIB_SUFFIX "lib")
    set(DYNAMIC_LIB_SUFFIX "dll")

    if (MSVC)
        # 设置Visual Studio的不同编译配置
        set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 /Gy /EHsc")
        set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /Zi /O1 /Ob2 /Oi /Os /D NDEBUG /GS-")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1 /D NDEBUG")
        set(CMAKE_CXX_FLAGS_RELEASE "/MD /Zi /O2 /Ob1 /D NDEBUG")
    endif()
endif()

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/Bin/${PLATFORM_NAME}/${ARCH_NAME}/${CMAKE_BUILD_TYPE}")
set(LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}")