//
// Created by andrew on 2022/2/21.
//

#ifndef DLMS_DLMS_BASH_H
#define DLMS_DLMS_BASH_H
#include <iostream>
#include <functional>
#include "status.h"
#include "thread_manager.h"


class Plugin;
class IContext {
public:


public:
    virtual ~IContext() = default;

    /**
     * @brief 主进程初始化
     *
     * @return 0:成功，其他：失败
     */
    virtual Status Init() = 0;

    /**
     * @brief 启动主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual Status Start() = 0;

    /**
     * @brief 停止主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual Status Stop() = 0;

    /**
     * @brief 退出主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual Status Reset() = 0;

    /**
     * @brief 获取插件对象
     *
     * @return nullptr:失败，其他：成功
     */
    virtual Plugin *GetPlugin(std::string &pluginName, std::string &type) = 0;

    // 将需要工作的线程放到Push里面
    virtual Status Dispatch(Func workFunction) = 0;
};


class IConfig {
public:
    virtual ~IConfig() = default;





};












#endif //DLMS_DLMS_BASH_H
