//
// Created by andrew on 2022/2/21.
//

#ifndef DLMS_PLUGIN_H
#define DLMS_PLUGIN_H
#include <iostream>
#include <memory>

#include "dlms_bash.h"

/*
 * 实际项目中随时可以替换成动态库插件形式，这里为demo代码采用直接链接编译的方式使用
 * */

enum PluginType
{
    /// \brief A World plugin
    WORLD_PLUGIN,
    /// \brief A Model plugin
    MODEL_PLUGIN,
    /// \brief A Sensor plugin
    SENSOR_PLUGIN,
    /// \brief A System plugin
    SYSTEM_PLUGIN,
    /// \brief A Visual plugin
    VISUAL_PLUGIN,
    /// \brief A GUI plugin
    GUI_PLUGIN
};


class Plugin {
public:
    enum PluginStatus : uint8_t {
        PLUGIN_UNKNOWN             = 0,
        PLUGIN_INIT                = 1,
        PLUGIN_RUNNING             = 2,
        PLUGIN_STOP                = 3,
        PLUGIN_Reset                = 4,
    };
    //

public:
    virtual ~Plugin() = default;

    /**
     * @brief 插件初始化
     *
     * @param lpIDlms 主框架对象指针
     */
    virtual int32_t Init(IDlms *lpIDlms) = 0;

    virtual int32_t Start() = 0;

    virtual int32_t Stop() = 0;

    virtual int32_t Reset() = 0;

    // 获取插件名字
    virtual std::string GetHandleName() = 0;



protected:
    volatile PluginStatus       m_pluginStatus{PLUGIN_UNKNOWN};
    PluginType type;
    std::string handleName; // name of the plugin
};




#endif //DLMS_PLUGIN_H
