#ifndef BASECAMERA_H
#define BASECAMERA_H

#include "ivcamera.h"

class BaseCamera : public IVCamera
{
public:
    virtual ~BaseCamera() override {}

    virtual void startPlayData() override = 0;
    virtual void stop() override = 0;
    virtual bool isPlaying() override = 0;
    virtual void setPlayRate(int playRate) override = 0;
};

#endif // BASECAMERA_H
