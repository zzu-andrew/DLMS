//
// Created by wangyz38535 on 2022/6/28.
//

#ifndef DLMS_WEBSOCKET_PLUGIN_H
#define DLMS_WEBSOCKET_PLUGIN_H

#include <cstring>
#include <unistd.h>
#include "CivetServer.h"
#include "plugin.h"
#include "websocket_server.h"
#include "websocket_client.h"


class Websocket : public Plugin {
public:
    ~Websocket() override;

    Status Init(IContext *lpIDlms, std::string& pluginName) override;

    Status Start() override;

    Status Stop() override;

    Status Reset() override;


    std::string GetHandleName() override;

    Status SendAndReceive(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) override;

    Status Send(PluginServiceType in, void *lpInData) override;

    Status Notify(PluginServiceType in, void *lpInData) override;

    bool ServiceSupport(PluginServiceType serviceType) override;

private:
    WebsocketServer websocketServer;

};


#endif //DLMS_WEBSOCKET_PLUGIN_H
