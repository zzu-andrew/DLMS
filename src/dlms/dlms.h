//
// Created by andrew on 2022/2/13.
//

#ifndef DLMS_DLMS_H
#define DLMS_DLMS_H

#include <dlms_bash.h>

class CDlms : public IDlms {
public:
    ~CDlms() override = default;

    virtual int32_t Init() = 0;

    virtual int32_t Start() = 0;

    virtual int32_t Stop() = 0;

    virtual int32_t Exit() = 0;

private:


};





#endif //DLMS_DLMS_H
