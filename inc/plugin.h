//
// Created by andrew on 2022/2/21.
//

#ifndef DLMS_PLUGIN_H
#define DLMS_PLUGIN_H
#include <iostream>
#include "dlms_bash.h"

class IPlugin {
public:
    enum PluginStatus : uint8_t {
        PLUGIN_UNKNOWN             = 0,
        PLUGIN_INIT                = 1,
        PLUGIN_RUNNING             = 2,
        PLUGIN_STOP                = 3,
        PLUGIN_EXIT                = 4,
    };

public:
    virtual ~IPlugin() = default;

    /**
     * @brief 插件初始化
     *
     * @param lpIDlms 主框架对象指针
     */
    virtual int32_t Init(IDlms *lpIDlms) = 0;

    virtual int32_t Start() = 0;

    virtual int32_t Stop() = 0;

    virtual int32_t Exit() = 0;




protected:
    volatile PluginStatus       m_pluginStatus{PLUGIN_UNKNOWN};
};




#endif //DLMS_PLUGIN_H
