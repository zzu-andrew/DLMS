//
// Created by wangyz38535 on 2022/6/28.
//

#ifndef DLMS_WEBSOCKET_CLIENT_H
#define DLMS_WEBSOCKET_CLIENT_H

#include "status.h"
#include "websocket_plugin.h"


class WebsocketClient : public Websocket {
public:
    WebsocketClient() = default;
    Status Init(IContext *lpContext, std::string pluginName) override;

    Status Start() override;

    Status Stop() override;

    Status Reset() override;

private:

};


#endif //DLMS_WEBSOCKET_CLIENT_H
