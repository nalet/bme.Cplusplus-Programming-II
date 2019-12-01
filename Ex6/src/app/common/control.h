/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <memory>

// TODO: Remove compile time dependency with observer pattern
// control should compile without including widget.h
//#include "widget.h"
#include "icontrol.h"
// ------------------------------------------------------------

// Forward declarations
class VCamera;
class DataBufferPool;

class Control :  public QWidget, IControl
{

public:
    Control(IControl *parent);
    ~Control() override;

    // TODO: Move to interface
    void displayMsg(std::string tag, std::string msg) override;
    void setData(DataBufferPtr dataJunk) override;
    // ------------------------------------------------------------

    void init();
    void startPlaying();
    void stopPlaying();
    bool isPlaying() const;
    void setPlayRate(int playRate);

private:
    IControl* m_widget;
    uint m_height;
    uint m_widht;

    std::unique_ptr<VCamera> m_player;
    std::shared_ptr<DataBufferPool> m_dataPool;
};
#endif // CONTROL_H
