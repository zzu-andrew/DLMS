# 定义动态库，虽然最终是生成so文件，也被称为可执行文件的一种，但是动态库并不需要链接全部文件，有些依赖的文件只需要给出头文件即可
add_library(websocket SHARED
        websocket_plugin.cpp
        websocket_server.cpp
        websocket_client.cpp)

target_link_libraries(websocket
        PUBLIC pthread)
target_include_directories(websocket
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/3rd/civetweb/include
        PUBLIC ${PROJECT_SOURCE_DIR}/utils)
target_compile_definitions(websocket
        PUBLIC pthread
        PUBLIC dl)