

# 设置静态库文件目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# 动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/plugins)
# 可执行文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)



add_library(websocket SHARED
        websocket/websocket_plugin.cpp
        websocket/websocket_server.cpp
        websocket/websocket_client.cpp)
target_link_libraries(websocket
        PUBLIC pthread)
target_include_directories(websocket
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/3rd/civetweb)




