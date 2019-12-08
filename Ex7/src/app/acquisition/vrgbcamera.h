#ifndef VRGBCAMERA_H
#define VRGBCAMERA_H

#include <thread>
#include "dataBuffer.h"
#include "icontrol.h"
#include "basecamera.h"

// Forward declarations
class IControl;
class DataBufferPool;

class VRgbCamera final : public BaseCamera
{
public:
    VRgbCamera(IControl* control, std::shared_ptr<DataBufferPool> dataPool);
    ~VRgbCamera() override;

    void startPlayData() override;
    void stop() override;
    bool isPlaying() override;
    void setPlayRate(int playRate) override;

private:
    void run() ;
    bool readImage(DataBufferPtr data);

    std::string m_tag;
    std::thread m_acquireThread;
    bool m_play;

    // TODO: Remove compile time dependency
    IControl* m_control;
    // ------------------------------------------------------------

    int m_playRate;
    std::shared_ptr<DataBufferPool> m_dataPool;
    int offset;
};

#endif // VRGBCAMERA_H
