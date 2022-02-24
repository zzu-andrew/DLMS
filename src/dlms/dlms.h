//
// Created by andrew on 2022/2/13.
//

#ifndef DLMS_DLMS_H
#define DLMS_DLMS_H
#include <string>
#include <map>

#include "plugin.h"
#include <dlms_bash.h>

class CDlms : public IDlms {
public:
    ~CDlms() override = default;

    int32_t Init() override;

    int32_t Start() override;

    int32_t Stop() override;

    int32_t Exit() override;

    IPlugin* GetPluginByName(std::string& pluginName) override;




private:
    std::map<std::string, IPlugin*> m_mapPlugin;

};





#endif //DLMS_DLMS_H
