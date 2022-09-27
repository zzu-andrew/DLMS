//
// Created by wangyz38535 on 2022/6/28.
//

#ifndef DLMS_WEBSOCKET_SERVER_H
#define DLMS_WEBSOCKET_SERVER_H

#include <cstring>
#include <unistd.h>
#include "CivetServer.h"
#include "plugin.h"
#include "dlms_error.h"
#include "status.h"
#include "websocket_plugin.h"



#ifdef USE_WEBSOCKET
class WebSocketHandler : public CivetWebSocketHandler {

    virtual bool handleConnection(CivetServer *server,
                                  const struct mg_connection *conn) {
        printf("WS connected\n");
        return true;
    }

    virtual void handleReadyState(CivetServer *server,
                                  struct mg_connection *conn) {
        printf("WS ready\n");

        const char *text = "Hello from the websocket ready handler";
        mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, text, strlen(text));
    }

    virtual bool handleData(CivetServer *server,
                            struct mg_connection *conn,
                            int bits,
                            char *data,
                            size_t data_len) {
        printf("WS got %lu bytes: ", (long unsigned)data_len);
        fwrite(data, 1, data_len, stdout);
        printf("\n");

        mg_websocket_write(conn, MG_WEBSOCKET_OPCODE_TEXT, data, data_len);
        return (data_len<4);
    }

    virtual void handleClose(CivetServer *server,
                             const struct mg_connection *conn) {
        printf("WS closed\n");
    }
};
#endif


class WebsocketServer : public Websocket {
public:

    Status Init(IContext *lpContext, std::string pluginName) override;

    Status Start() override;

    Status Stop() override;

    Status Reset() override;


private:
    WebSocketHandler *lpWebSocketHandler{nullptr};
    CivetServer *lpCivetServer{nullptr};
};




#endif //DLMS_WEBSOCKET_SERVER_H
