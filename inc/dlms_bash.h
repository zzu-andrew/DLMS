//
// Created by andrew on 2022/2/21.
//

#ifndef DLMS_DLMS_BASH_H
#define DLMS_DLMS_BASH_H
#include <iostream>

class IDlms {
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
    virtual int32_t Exit() = 0;
};


#endif //DLMS_DLMS_BASH_H