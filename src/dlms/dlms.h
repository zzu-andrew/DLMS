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


class CDlms : public IDlms {
public:
    ~CDlms() override = default;

    int32_t Init() override;

    int32_t Start() override;

    int32_t Stop() override;

    int32_t Reset() override;

    Plugin* GetPlugin(std::string& pluginName) override;



private:
    PluginManager pluginManager;


};



class CConfig : public IConfig {
public:
    ~CConfig() override = default;

    int32_t ParseCommandLine(int32_t argc, char* argv[]);


private:
    std::unordered_map<char, std::string> config;
    JsonProxy* jsonProxy;
};





#endif //DLMS_DLMS_H
