#ifndef IVCAMERA_H
#define IVCAMERA_H


class IVCamera
{
public:
    virtual ~IVCamera() {} //this is essential

    virtual void startPlayData() = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() = 0;
    virtual void setPlayRate(int playRate) = 0;
};

#endif // IVCAMERA_H
