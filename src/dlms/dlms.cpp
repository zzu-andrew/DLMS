//
// Created by andrew on 2022/2/13.
//
#include <iostream>
#include <glog/logging.h>

#include "dlms.h"
#include "json.hpp"
#include "dlms_macro.h"
#include "dlms_error.h"
#include "thread_manager.h"

using json=nlohmann::json;

using namespace std;


int main(int argc, char* argv[]) {

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "./log";
    LOG(INFO) << "Hello, world!";

    CContext context;
    // 1. 解析命令行参数
    context.ParseCommandLine(argc, argv);

    context.Init();
    context.Start();

    context.Stop();
    context.Reset();



    //...... DoSomething
    //Shutdown google's logging library.
    google::ShutdownGoogleLogging();



    return 0;
}


Status CContext::Init() {

    // 具体的线程个数从配置文件中获取
    lpThreadManager = new (std::nothrow) ThreadManager(10);
    if (nullptr == lpThreadManager) {

        return Status::OutOfMemory("");
    }


    return Status::Ok();
}

Status CContext::Start() {


    return Status::Ok();
}

Status CContext::Stop() {
    return Status::Ok();
}

Status CContext::Reset() {

    delete lpThreadManager;

    return Status::Ok();
}

Plugin *CContext::GetPlugin(std::string &pluginName) {

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
    return Status::InvalidArgument("");
}

#define GET_CASE_INFO(X)                                                \
    case X:                                                             \
      configMap.emplace(std::make_pair(X, POINTER_SAFE(optarg)));       \
      break;

Status CConfig::ParseCommandLine(int32_t argc, char *argv[]) {

    int ch;
    std::string opts = "a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x:y:z:"
                       "A:B:C:D:E:F:G:H:I:J:K:L:M:N:O:P:Q:R:S:T:U:V:W:X:Y:Z:";
    while( (ch = getopt(argc, argv, opts.c_str())) != -1 )
    {
        switch(ch)
        {
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
                printf("default, result=%c\n",ch);
                break;
        }
    }
    return Status::Ok();
}
