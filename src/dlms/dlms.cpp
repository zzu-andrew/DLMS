//
// Created by andrew on 2022/2/13.
//
#include <iostream>
#include <glog/logging.h>

#include "dlms.h"
#include "json.hpp"

using json=nlohmann::json;

using namespace std;

void JsonTest() {
    // 创建一个json对象(null)
    json j;

    //添加一个存储为double的数字
    j["pi"] = 3.141;

    // 添加一个布尔值
    j["happy"] = true;

    // 添加一个存储为std :: string的字符串
    j["name"] = "Niels";

    // 通过传递nullptr添加另一个空对象
    j["nothing"] = nullptr;

    // 在对象中添加对象
    j["answer"]["everything"]["data"] = 42;

    //添加一个数组，其存储为std：：vector（使用初始化列表）
    j["list"] = { 1, 0, 2 };

    // 在一个对象中添加另一个对象
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };



    // 也可以通过直接赋值方式创建json对象，两种方式创建结果相同
    json j2 = {
            {"pi", 3.141},
            {"happy", true},
            {"name", "Niels"},
            {"nothing", nullptr},
            {"answer", {
                           {"everything", 42}
                   }},
            {"list", {1, 0, 2}},
            {"object", {
                           {"currency", "USD"},
                         {"value", 42.99}
                   }}
    };
    cout << j << endl;
    cout << endl;
    cout << j2 << endl;


};



int main(int argc, char* argv[]) {

    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "./log";
    LOG(INFO) << "Hello, world!";

    CDlms dlms;
    // 1. 解析命令行参数
    dlms.ParseCommandLine(argc, argv);








    //...... DoSomething
    //Shutdown google's logging library.
    google::ShutdownGoogleLogging();


    JsonTest();

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

int32_t CDlms::Reset() {
    return 0;
}

Plugin *CDlms::GetPlugin(std::string &pluginName) {

    //auto iter = m_mapPlugin.find(pluginName);
    //if (iter == m_mapPlugin.end()) {
    //    return nullptr;
    //}

    //return iter->second;
    return nullptr;
}

int32_t CDlms::ParseCommandLine(int32_t argc, char **argv) {
    return config.ParseCommandLine(argc, argv);
}

#define POINTER_SAFE(lp)        ((nullptr == lp) ? "null" : lp)

#define GET_CASE_INFO(X)                                                \
    case X:                                                             \
      configMap.emplace(std::make_pair(X, POINTER_SAFE(optarg)));       \
      break;

int32_t CConfig::ParseCommandLine(int32_t argc, char *argv[]) {

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
                break;
            default:
                printf("default, result=%c\n",ch);
                break;
        }
    }
    return 0;
}
