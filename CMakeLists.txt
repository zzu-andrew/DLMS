cmake_minimum_required (VERSION 3.16)
project (DLMS
        VERSION 0.1.0
        DESCRIPTION "Distributed Linux monitoring system"
        HOMEPAGE_URL https://github.com/zzu-andrew/DLMS
        LANGUAGES CXX C
        )

add_definitions("-O0 -g -Wall")


# Linux 分布式监控系统
set (CPACK_PACKAGE_NAME DLMS)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Distributed Linux monitoring system")
set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

# 设置静态库文件目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# 动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/plugins)
# 可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

message(STATUS　${CPACK_PACKAGE_VERSION})


add_subdirectory(3rd/glog)
#add_subdirectory(3rd/civetweb)
add_subdirectory(plugins)


add_executable(dlms
        src/dlms/dlms.cpp
        src/dlms/plugin_manager.cpp
        )
target_include_directories(dlms
        PUBLIC inc
        PUBLIC 3rd/nlohmann
        PUBLIC src/dlms
        PUBLIC utils)
target_link_directories(dlms
        PUBLIC lib)
target_link_libraries(dlms
        PUBLIC glog
        PUBLIC dl)

# 编译依赖，如果添加依赖编译时会将对应的目标也进行编译
add_dependencies(dlms websocket)

add_subdirectory(test)







