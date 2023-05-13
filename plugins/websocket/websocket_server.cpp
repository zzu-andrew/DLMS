//
// Created by wangyz38535 on 2022/6/28.
//

#include "websocket_server.h"

#define DOCUMENT_ROOT "."
#define PORT "8081"


#include "CivetServer.h"
#include <cstring>
#include <unistd.h>

#define DOCUMENT_ROOT "."
#define PORT "8081"
#define EXAMPLE_URI "/example"
#define EXIT_URI "/exit"


/* Exit flag for main loop */
volatile bool exitNow = false;



class ABHandler : public CivetHandler
{
public:
    bool
    handleGet(CivetServer *server, struct mg_connection *conn)
    {
        mg_printf(conn,
                  "HTTP/1.1 200 OK\r\nContent-Type: "
                  "text/html\r\nConnection: close\r\n\r\n");
        mg_printf(conn, "<html><body>");
        mg_printf(conn, "<h2>This is the AB handler!!!</h2>");
        mg_printf(conn, "</body></html>\n");
        return true;
    }
};


Status WebsocketServer::Start() {



    // 将需要工作的线程注册到主框架中

    return Status::Ok();
}

Status WebsocketServer::Init(IContext *lpContext, std::string pluginName) {
    Websocket::Init(lpContext, pluginName);
    // 服务端启动
    const char *options[] = {
        "document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0};


    std::vector<std::string> cpp_options;
    cpp_options.reserve(sizeof(options) / sizeof(options[0]) - 1);
    for (int32_t i = 0; i < static_cast<int32_t>((sizeof(options) / sizeof(options[0]) - 1)); ++i) {
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
    return Status();
}

Status WebsocketServer::Stop() {
    return Status();
}
Status WebsocketServer::Reset() {

    mg_exit_library();
    return Status();
}
