//
// Created by wangyz38535 on 2022/6/28.
//

#ifndef DLMS_WEBSOCKET_PLUGIN_H
#define DLMS_WEBSOCKET_PLUGIN_H

#include <cstring>
#include <unistd.h>
#include "CivetServer.h"
#include "plugin.h"

class Websocket : public Plugin {
public:
    ~Websocket() override;

    void *GetInterface(const char *uuid) override;

    Status Init(IContext *lpContext, std::string pluginName) override;

    Status Start() override;

    Status Stop() override;

    Status Reset() override;

    std::string GetName() override;

    Status SendSync(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) override;

    Status SendAsync(PluginServiceType in, void *lpInData) override;

    Status Notify(PluginServiceType in, void *lpInData) override;

    bool Support(PluginServiceType serviceType) override;

    Status PostMessage(PluginServiceType in, void *lpInData) override;
protected:
    IContext *lpContext{nullptr};
};


#endif //DLMS_WEBSOCKET_PLUGIN_H
