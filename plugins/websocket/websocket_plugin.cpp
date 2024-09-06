//
// Created by wangyz38535 on 2022/6/28.
//

#include "websocket_plugin.h"
#include "websocket_server.h"
#include "websocket_client.h"

Websocket::~Websocket() = default;

Status Websocket::Init(IContext *lpCtx, std::string pluginName) {

    // 初始化websocket库
    mg_init_library(0);

    // 根据配置来
    lpContext = lpCtx;

    return Status::Ok();
}

Status Websocket::Notify(PluginServiceType in, void *lpInData) {
    return Status::Ok();
}

Status Websocket::Start() {


    return Status::Ok();
}

Status Websocket::Stop() {
    return Status::Ok();
}

Status Websocket::Reset() {
    return Status::Ok();
}

std::string Websocket::GetName() {
    return std::string();
}

Status Websocket::SendSync(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) {
    return Status::Ok();
}

Status Websocket::SendAsync(PluginServiceType in, void *lpInData) {
    return Status::Ok();
}

bool Websocket::Support(PluginServiceType serviceType) {
    return false;
}

Status Websocket::PostMessage(PluginServiceType in, void *lpInData) {
    return Status();
}

void *Websocket::GetInterface(const char *uuid) {


    return nullptr;
}

#ifdef __cplusplus
extern "C" {
const char *GetVersion() {
    return "";
}

Plugin *CreatePlugin(const char *pluginType) {
    try {
        std::string type(pluginType);
        if (type == "client") {
            return new WebsocketClient;
        } else {
            return new WebsocketServer;
        }
    } catch (const std::exception& e) {
        return nullptr;
    }
}
void DeletePlugin(Plugin *plugin) {
    delete plugin;
}
}

#endif

