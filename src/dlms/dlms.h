//
// Created by andrew on 2022/2/13.
//

#ifndef DLMS_DLMS_H
#define DLMS_DLMS_H

#include <string>
#include <map>
#include <unordered_map>

#include "plugin.h"
#include <dlms_bash.h>
#include "plugin_manager.h"
#include "json_proxy.h"
#include "thread_manager.h"


class CConfig : public IConfig {
public:
    ~CConfig() override;

    Status ParseCommandLine(int32_t argc, char *argv[]);

    Status LoadJsonFromFile();

    JsonProxy& GetJsonProxy();

private:
    std::unordered_map<char, std::string> configMap;
    JsonProxy *lpJsonProxy{nullptr};
};

class CContext : public IContext {
public:
    ~CContext() override = default;

    Status Init() override;

    Status Start() override;

    Status Stop() override;

    Status Reset() override;

    Plugin *GetPlugin(std::string &pluginName, std::string &type) override;

    // 将需要工作的线程放到Push里面
    Status Dispatch(Func workFunction) override;

    // 如果某些函数不需要再执行了就Pop掉，之后主框架就不在执行该函数了
    Status ParseCommandLine(int32_t argc, char *argv[]);

    Status LoadConfig();

    Status LoadPlugins();

public:


private:
    PluginManager pluginManager;
    CConfig config;
    ThreadManager *lpThreadManager{nullptr};
};


#endif //DLMS_DLMS_H
