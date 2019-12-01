/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef VCAMERA_H
#define VCAMERA_H

#include <thread>
#include "dataBuffer.h"
#include "icontrol.h"

// Forward declarations
class Control;
class DataBufferPool;

/**
 * @brief The VCamera class
 *
 * Note: Inheritating is not allowed since starting a thread in the constructor can be problematic for derived classes
 */
class VCamera final
{

public:
    VCamera(IControl* control, std::shared_ptr<DataBufferPool> dataPool);
    ~VCamera();

    void startPlayData();
    void stop();
    bool isPlaying();
    void setPlayRate(int playRate);

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

#endif // VCAMERA_H
