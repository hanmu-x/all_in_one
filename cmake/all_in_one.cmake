# 添加第三方依赖包
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(add_FetchContent_MakeAvailable.cmake)
endif()

# 设置all_in_one的下载目录
if("${ALL_IN_ONE_FETCH_ROOT}" STREQUAL "")
    set(ALL_IN_ONE_FETCH_ROOT ${CMAKE_SOURCE_DIR}/ao_ext)
endif()


# 指定版本
set(SILLY_UTIL_TAG  master)  
set(ALL_IN_ONE_GIT_URL  "https://gitee.com/master-turtle/all_in_one.git")  


FetchContent_Declare(
  all_in_one
  GIT_REPOSITORY    ${ALL_IN_ONE_GIT_URL}
  SOURCE_DIR        ${ALL_IN_ONE_FETCH_ROOT}/all_in_one
)

FetchContent_MakeAvailable(all_in_one)

# 下载完成后 拷贝检测环境的.cmake文件
IF(NOT EXISTS "${CMAKE_SOURCE_DIR}/ao_cmake")
    FILE(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/ao_cmake")
ENDIF()
execute_process(COMMAND ${CMAKE_COMMAND} -E  copy "${ALL_IN_ONE_FETCH_ROOT}/all_in_one/cmake/env_module.cmake" "${CMAKE_SOURCE_DIR}/ao_cmake/env_module.cmake")
execute_process(COMMAND ${CMAKE_COMMAND} -E  copy "${ALL_IN_ONE_FETCH_ROOT}/all_in_one/.clang-format" "${CMAKE_SOURCE_DIR}/.clang-format")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/ao_cmake;${CMAKE_MODULE_PATH}")
include(env_module)
\

include_directories("${ALL_IN_ONE_FETCH_ROOT}/all_in_one/core")