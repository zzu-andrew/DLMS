//
// Created by andrew on 2022/2/13.
//
#include <iostream>
#include <csignal>
#include <glog/logging.h>

#include "dlms.h"
#include "json.hpp"
#include "status.h"
#include "dlms_macro.h"
#include "dlms_error.h"
#include "thread_manager.h"

using json = nlohmann::json;

using namespace std;

static bool running = true;

static void SignalInterrupt(int sig) {
    printf("WrkProcess .I get signal.%d threadid:%lu/n",sig, pthread_self());


    running = false;
}

int main(int argc, char *argv[]) {

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "./log";
    LOG(INFO) << "Hello, world!";

    struct sigaction action{};

    /* 设置信号忽略 */
    sigemptyset(&action.sa_mask);
    //sigaddset(&action.sa_mask, SIGINT);

    action.sa_handler = SignalInterrupt; //这个地方也可以是函数

    action.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &action, nullptr);

    CContext context;
    // 1. 解析命令行参数
    auto status = context.ParseCommandLine(argc, argv);
    if (!status.ok()) {
        goto out;
    }

    // 2. 加载配置
    status = context.LoadConfig();
    if (!status.ok()) {
        //goto out;
    }

    // 3. 加载插件
    status = context.LoadPlugins();
    if (!status.ok()) {
        goto out;
    }

    context.Init();
    if (!status.ok()) {
        goto out;
    }

    context.Start();
    if (!status.ok()) {
        goto out;
    }

    while (running) {
        printf("running = %d",  running);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    context.Stop();
    if (!status.ok()) {
        goto out;
    }

    context.Reset();
    if (!status.ok()) {
        goto out;
    }

    google::ShutdownGoogleLogging();

    return 0;
out:
    LOG(INFO) << status.ToString();
    return -1;
}


Status CContext::Init() {

    // 具体的线程个数从配置文件中获取
    //auto json = config.GetJsonProxy().GetJsonObj();
    //auto number = json["DLMS"]["Worker"]["ThreadNumber"];
    //if (!number.is_number()) {
    //    return Status::NotFound("ThreadNumber is is not exists");
    //}
    // 创建工作线程池
    lpThreadManager = new(std::nothrow) ThreadManager(10);
    if (nullptr == lpThreadManager) {

        return Status::OutOfMemory("");
    }


    for (auto &plugins : pluginManager.GetPluginsMap()) {

        for (auto & plugin : plugins.second) {
            auto status = plugin.second->Init(this, plugins.first);
            if (!status.ok()) {
                return status;
            }
        }
    }


    return Status::Ok();
}

Status CContext::Start() {

    // 注册信号

    for (auto &plugins : pluginManager.GetPluginsMap()) {

        for (auto & plugin : plugins.second) {
            auto status = plugin.second->Start();
            if (!status.ok()) {
                return status;
            }
        }
    }


    return Status::Ok();
}

Status CContext::Stop() {

    lpThreadManager->Stop();
    return Status::Ok();
}

Status CContext::Reset() {

    delete lpThreadManager;

    return Status::Ok();
}

Plugin *CContext::GetPlugin(std::string &pluginName, std::string &type) {

    //auto iter = m_mapPlugin.find(pluginName);
    //if (iter == m_mapPlugin.end()) {
    //    return nullptr;
    //}

    //return iter->second;
    return nullptr;
}

Status CContext::ParseCommandLine(int32_t argc, char **argv) {
    return config.ParseCommandLine(argc, argv);
}

Status CContext::Dispatch(Func workFunction) {


    lpThreadManager->Dispatch(workFunction);
    return Status::InvalidArgument("");
}

Status CContext::LoadConfig() {
    auto status = config.LoadJsonFromFile();
    if (!status.ok()) {
        return status;
    }

    return Status::Ok();
}
Status CContext::LoadPlugins() {
    return pluginManager.LoadPlugin();
}

#define GET_CASE_INFO(X)                                                \
    case X:                                                             \
      configMap.emplace(std::make_pair(X, POINTER_SAFE(optarg)));       \
      break;

Status CConfig::ParseCommandLine(int32_t argc, char *argv[]) {

    int ch;
    std::string opts = "a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x:y:z:"
                       "A:B:C:D:E:F:G:H:I:J:K:L:M:N:O:P:Q:R:S:T:U:V:W:X:Y:Z:";
    while ((ch = getopt(argc, argv, opts.c_str())) != -1) {
        switch (ch) {
            GET_CASE_INFO('a');
            GET_CASE_INFO('b');
            GET_CASE_INFO('c');
            GET_CASE_INFO('d');
            GET_CASE_INFO('e');
            GET_CASE_INFO('f');
            GET_CASE_INFO('g');
            GET_CASE_INFO('h');
            GET_CASE_INFO('i');
            GET_CASE_INFO('j');
            GET_CASE_INFO('k');
            GET_CASE_INFO('l');
            GET_CASE_INFO('m');
            GET_CASE_INFO('n');
            GET_CASE_INFO('o');
            GET_CASE_INFO('p');
            GET_CASE_INFO('q');
            GET_CASE_INFO('r');
            GET_CASE_INFO('s');
            GET_CASE_INFO('t');
            GET_CASE_INFO('u');
            GET_CASE_INFO('v');
            GET_CASE_INFO('w');
            GET_CASE_INFO('x');
            GET_CASE_INFO('y');
            GET_CASE_INFO('z');
            case '?':
                configMap['?'] = "Bad option!";
                return Status::InvalidArgument("");
            default:
                printf("default, result=%c\n", ch);
                break;
        }
    }
    return Status::Ok();
}

Status CConfig::LoadJsonFromFile() {

    auto iter = configMap.find('j');
    if (iter == std::end(configMap)) {
        return Status::NotFound("Config json is not found");
    }

    std::string path = get_current_dir_name();
    std::string filename = iter->second;

    lpJsonProxy = new JsonProxy(path, filename);
    if (nullptr == lpJsonProxy) {
        return Status::OutOfMemory("Failed to create json proxy");
    }

    std::cout << lpJsonProxy->GetJsonObj().dump() << std::endl;

    return Status::Ok();
}

CConfig::~CConfig() {
    delete lpJsonProxy;
}

JsonProxy &CConfig::GetJsonProxy() {
    return *lpJsonProxy;
}
