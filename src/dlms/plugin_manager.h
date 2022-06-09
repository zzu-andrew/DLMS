//
// Created by andrew on 2022/6/10.
//

#ifndef DLMS_PLUGIN_MANAGER_H
#define DLMS_PLUGIN_MANAGER_H
#include <map>
#include <string>


#include "plugin.h"


class PluginManager {
public:
    int32_t LoadPlugin(const std::string& path, const std::string& pluginName);

    int32_t LoadPlugin(const std::string& path);

    Plugin *GetPlugin(const std::string& pluginName);



private:
    std::map<std::string, Plugin*> mapPlugins;

};


#endif //DLMS_PLUGIN_MANAGER_H
