//
// Created by andrew on 2022/2/21.
//

#ifndef DLMS_DLMS_BASH_H
#define DLMS_DLMS_BASH_H
#include <iostream>
#include <functional>

class Plugin;
class IDlms {
public:
    typedef typename std::function<int32_t ()> Func;

public:
    virtual ~IDlms() = default;

    /**
     * @brief 主进程初始化
     *
     * @return 0:成功，其他：失败
     */
    virtual int32_t Init() = 0;

    /**
     * @brief 启动主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual int32_t Start() = 0;

    /**
     * @brief 停止主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual int32_t Stop() = 0;

    /**
     * @brief 退出主进程
     *
     * @return 0:成功，其他：失败
     */
    virtual int32_t Reset() = 0;

    /**
     * @brief 获取插件对象
     *
     * @return nullptr:失败，其他：成功
     */
    virtual Plugin *GetPlugin(std::string &pluginName) = 0;

    // 将需要工作的线程放到Push里面
    virtual uint32_t PushWorker(Func workFunction) = 0;
    // 如果某些函数不需要再执行了就Pop掉，之后主框架就不在执行该函数了
    virtual int32_t PopWorker(uint32_t Index) = 0;
};


class IConfig {
public:
    virtual ~IConfig() = default;





};












#endif //DLMS_DLMS_BASH_H
