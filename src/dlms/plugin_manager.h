//
// Created by andrew on 2022/6/10.
//

#ifndef DLMS_PLUGIN_MANAGER_H
#define DLMS_PLUGIN_MANAGER_H
#include <map>
#include <string>
#include <memory>

#include "plugin.h"


class PluginManager {
public:
    typedef std::map<std::string, std::map<std::string, Plugin*>> PluginsMap;

    Status LoadPlugin(const std::string& path, const std::string& pluginName);

    Status LoadPlugin();

    Plugin *GetPlugin(const std::string& pluginName, std::string& type);

    PluginsMap &GetPluginsMap() { return mapPlugins; }


private:
    PluginsMap mapPlugins;

};


#endif //DLMS_PLUGIN_MANAGER_H
