//
// Created by andrew on 2022/2/13.
//
#include <iostream>
#include <glog/logging.h>

#include "dlms.h"



int main(int argc, char* argv[]) {

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "./log";

    LOG(INFO) << "Hello, world!";



    std::cout << "=====" << std::endl;

    //...... DoSomething
    //Shutdown google's logging library.
    google::ShutdownGoogleLogging();




    return 0;
}


int32_t CDlms::Init() {



    return 0;
}

int32_t CDlms::Start() {
    return 0;
}

int32_t CDlms::Stop() {
    return 0;
}

int32_t CDlms::Exit() {
    return 0;
}

IPlugin *CDlms::GetPluginByName(std::string &pluginName) {

    auto iter = m_mapPlugin.find(pluginName);
    if (iter == m_mapPlugin.end()) {
        return nullptr;
    }

    return iter->second;
}
