//
// Created by wangyz38535 on 2022/6/28.
//

#include "websocket_server.h"

#define DOCUMENT_ROOT "."
#define PORT "8081"

Status WebsocketServer::Start() {


    // 服务端启动
    const char *options[] = {
            "document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0};

    std::vector<std::string> cpp_options;
    cpp_options.reserve(sizeof(options) / sizeof(options[0]) - 1);
    for (int i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
        cpp_options.emplace_back(options[i]);
    }
    lpCivetServer = new(std::nothrow) CivetServer(cpp_options);
    if (nullptr == lpCivetServer) {
        return Status::OutOfMemory("New civet server failed!");
    }

    lpWebSocketHandler = new(std::nothrow) WebSocketHandler;
    if (nullptr == lpWebSocketHandler) {
        return Status::OutOfMemory("New web socket handler failed!");
    }

    lpCivetServer->addWebSocketHandler("/websocket", lpWebSocketHandler);
    // 将需要工作的线程注册到主框架中

    return Status::Ok();
}

int32_t WebsocketServer::Init(IContext *lpContext, std::string &pluginName) {


    return 0;
}
