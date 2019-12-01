#ifndef IVCAMERA_H
#define IVCAMERA_H


class IVCamera
{
public:
    IVCamera();
    virtual ~IVCamera();

    virtual void startPlayData();
    virtual void stop();
    virtual bool isPlaying();
    virtual void setPlayRate(int playRate);
};

#endif // IVCAMERA_H
