#ifndef ICONTROL_H
#define ICONTROL_H

#include "dataBuffer.h"

class IControl
{
public:
    virtual ~IControl() {} //this is essential {}
    virtual void displayMsg(const std::string &tag, const std::string &msg) = 0;
    virtual void setData(DataBufferPtr dataJunk) = 0;
};

#endif // ICONTROL_H
