#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H

#include <memory>
#include <iostream>
#include "basecamera.h"
#include "VCamera.h"
#include "vrgbcamera.h"

struct CameraFactory
{
    static std::unique_ptr<BaseCamera> create(const int type, IControl* control, std::shared_ptr<DataBufferPool> dataPool)
    {
        switch(type)
        {
            case 0:
                return std::unique_ptr<BaseCamera>(new VCamera(control, dataPool));
            case 1:
                return std::unique_ptr<BaseCamera>(new VRgbCamera(control, dataPool));
        }
        return std::unique_ptr<BaseCamera>(new VCamera(control, dataPool));
    }
};

#endif // CAMERAFACTORY_H
