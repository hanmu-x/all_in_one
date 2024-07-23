
cmake_minimum_required(VERSION 3.15)

project(MultiTool CXX)

foreach(dirname ${CMAKE_CURRENT_SOURCE_DIR})
    file(GLOB_RECURSE AO_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            "${dirname}/*.h"
            "${dirname}/*.hpp"
            "${dirname}/*.c"
            "${dirname}/*.cpp"
            )

endforeach()

# set(AO_STATIC_LIB 1)
if(AO_SHARE_LIB)
    message("构建动态库")
    add_library(${PROJECT_NAME} SHARED ${AO_SRC_FILES})
else()
    message("构建静态库")
    add_library(${PROJECT_NAME} STATIC ${AO_SRC_FILES})
endif()

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC JsonCpp::JsonCpp)



if(IS_LINUX)

endif()