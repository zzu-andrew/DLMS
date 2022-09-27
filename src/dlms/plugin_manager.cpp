//
// Created by andrew on 2022/6/10.
//
#include <dlfcn.h>


#include "plugin_manager.h"


Status PluginManager::LoadPlugin(const std::string &path, const std::string &pluginName) {
    return Status::Ok();
}

Status PluginManager::LoadPlugin() {

    // 打开共享库
    auto handler = dlopen("./plugins/libwebsocket.so", RTLD_NOW /* 立即加载 */);
    if (nullptr == handler) {
        return Status::NotFound("dlopen failed", dlerror());
    }

    auto CreateFunction = (Plugin* (*)(const char*))dlsym(handler, "CreatePlugin");
    if (CreateFunction == nullptr) {
        return Status::NotFound("dlsym failed", "websocket");
    }

    mapPlugins["Websocket"]["server"] = CreateFunction("server");
    mapPlugins["Websocket"]["client"] = CreateFunction("client");

    return Status::Ok();
}

Plugin *PluginManager::GetPlugin(const std::string &pluginName, std::string& type) {
    return nullptr;
}
