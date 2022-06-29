

add_library(websocket SHARED
        websocket/websocket_plugin.cpp
        websocket/websocket_server.cpp
        websocket/websocket_client.cpp)
target_link_libraries(websocket
        PUBLIC pthread)
target_include_directories(websocket
        PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/3rd/civetweb)




