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

// 服务函数根据类型进行参数和返回值的确认
enum PluginServiceType
{
    String  = 0x1,
    JSON    = 0x2,
    Binary  = 0x4,
    Integer = 0x8,
};

enum NotifyTypes
{
    NetBroken = 0,
    Quit = 1,
};

class IDlms;
class Plugin {
public:
    enum PluginStatus : uint8_t {
        PLUGIN_UNKNOWN             = 0,
        PLUGIN_INIT                = 1,
        PLUGIN_RUNNING             = 2,
        PLUGIN_STOP                = 3,
        PLUGIN_Reset               = 4,
    };
    //

public:
    virtual ~Plugin() = default;

    /**
     * @brief 插件初始化
     *
     * @param lpIDlms 主框架对象指针
     */
    virtual int32_t Init(IDlms *lpIDlms, std::string& pluginName) = 0;

    virtual int32_t Start() = 0;

    virtual int32_t Stop() = 0;

    virtual int32_t Reset() = 0;

    // 获取插件名字
    virtual std::string GetHandleName() = 0;

    virtual int32_t SendAndReceive(PluginServiceType in, void *lpInData, PluginServiceType out, void *lpOutData) = 0;

    virtual int32_t Send(PluginServiceType in, void *lpInData) = 0;

    virtual int32_t Notify(PluginServiceType in, void *lpInData) = 0;

    virtual bool ServiceSupport(PluginServiceType serviceType) = 0;

protected:
    volatile PluginStatus       pluginStatus{PLUGIN_UNKNOWN};
    uint32_t serviceSupportList;
    std::string handleName; // name of the plugin
};

#ifdef __cplusplus
extern "C" {
const char* GetVersion();
Plugin *CreatePlugin(const char* pluginName);
}

#endif



#endif //DLMS_PLUGIN_H
