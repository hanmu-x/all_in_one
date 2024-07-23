CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(all_in_one)

# 添加cmake模块路径
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
INCLUDE(env_module)


# 判断当前目录是否为 cmake的根目录,如果不是,则是被其他项目引用的,不需要编译测试,工具模块
IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    SET(AO_AS_PROJECT TRUE)
    SET(AO_AS_LIB FALSE)
ELSE ()
    SET(AO_AS_PROJECT FALSE)
    SET(AO_AS_LIB TRUE)
ENDIF ()


IF (AO_AS_PROJECT)
    MESSAGE(STATUS "作为单个工程编译")
    # 设置默认程序默认根目录，程序的默认数据目录
    ADD_DEFINITIONS("-DDEFAULT_AO_ROOT_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")
    ADD_DEFINITIONS("-DDEFAULT_AO_DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/data\"")

ELSEIF()
    MESSAGE(STATUS "作为嵌入库编译")
ENDIF ()


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/core)

##########################################
# Add sub dirs.
##########################################
ADD_SUBDIRECTORY(core)
IF (AO_AS_PROJECT)
    ADD_SUBDIRECTORY(test)
ENDIF ()



