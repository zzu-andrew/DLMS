//
// Created by wangyz38535 on 2022/6/28.
//

#include "websocket_plugin.h"




Websocket::~Websocket() = default;

Status Websocket::Init(IContext *lpIDlms, std::string &pluginName) {

    // 初始化websocket库
    mg_init_library(0);


    return Status::Ok();
}

Status Websocket::Send(PluginServiceType in, void *lpInData) {
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

std::string Websocket::GetHandleName() {
    return std::string();
}

Status Websocket::SendAndReceive(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) {
    return Status::Ok();
}

bool Websocket::ServiceSupport(PluginServiceType serviceType) {
    return false;
}