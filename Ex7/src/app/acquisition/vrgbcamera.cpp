/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <chrono>
#include "vrgbcamera.h"
#include "dataBufferPool.h"

// TODO: Remove compile time dependency
#include "control.h"
// ------------------------------------------------------------

VRgbCamera::VRgbCamera(IControl *control, std::shared_ptr<DataBufferPool> dataPool) :
    m_tag("Player"),
    m_play(false),
    m_control(control),
    m_playRate(33),
    m_dataPool(dataPool),
    offset(0)
{
    m_control->displayMsg(m_tag, "Player constructed");
}

VRgbCamera::~VRgbCamera()
{
    // Thread stopping
    m_play = false;

    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
}

void VRgbCamera::startPlayData()
{
    m_play = true;
    m_acquireThread = std::thread(&VRgbCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");
}

void VRgbCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
}

bool VRgbCamera::isPlaying()
{
    return m_play;
}

void VRgbCamera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}

//******* Below runs in own thread **********//
void VRgbCamera::run()
{
    while(m_play)
    {
        DataBufferPtr nextPtr = m_dataPool->getBuffer();
        if(readImage(nextPtr))
        {
            m_control->setData(nextPtr);
        }
        // Control frame rate
        int sleeptime = static_cast<int>(1000.0f / m_playRate) ;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }
}

bool VRgbCamera::readImage(DataBufferPtr data)
{
    int width = data->m_image.width();
    int height = data->m_image.height();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int val = x + offset;
            data->m_image.setPixel(x, y, qRgb(val - 10, val, val + 10));
        }
    }
    offset += 25;
    return true;
}
