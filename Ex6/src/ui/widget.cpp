/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <iostream>
#include <sstream>

#include "widget.h"
#include "ui_widget.h"
#include "dataBuffer.h"
#include "control.h"
#include "videoVisualizer.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_tag("Widget"),
    m_frameCount(0),
    GUI_RATE_MS(50),
    FPS_LABEL_RATE(500)
{    
    ui->setupUi(this);

    // Setup main control - passing widget to control
    m_appCtrl.reset( new Control(this) );

    // reset data container
    m_lastData.reset();

    // setup GUI
    initGUI();

    // Connect GUI
    connect(ui->play_pushButton, SIGNAL(clicked()), this, SLOT(playDataFromFile()));
    connect(ui->frameRateSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlayRate()));

    // Update GUI-timer to update images etc. every 20 ms
    m_guiUpdateTimer.reset( new QTimer(this));
    connect( m_guiUpdateTimer.get(), SIGNAL(timeout()), this, SLOT(updateGui()) );
    m_guiUpdateTimer->start(GUI_RATE_MS);

    // Frame Rate-timer
    m_frameRateTimer.reset( new QTimer(this));
    connect( m_frameRateTimer.get(), SIGNAL(timeout()), this, SLOT(updateFrameRate()) );
    m_frameRateTimer->start(FPS_LABEL_RATE);

}

Widget::~Widget()
{

}

// -----------------------------------------------------------------
// Functions called by Control (tight coupling)
// -----------------------------------------------------------------
void Widget::displayMsg(std::string tag, std::string msg)
{
    std::cout << " Info: " << tag << " : " <<  msg << std::endl;
}

void Widget::setData(DataBufferPtr data)
{
    m_lastData = data;
    ++m_frameCount;
}

// -----------------------------------------------------------------
// GUI
// -----------------------------------------------------------------
void Widget::initGUI()
{
    // Player Widget
    m_videoVisualizer.reset( new VideoVisualizer(ui->videoWidgetHolder) );

    // Frame Rate Slides
    ui->frameRateSlider->setMaximum(80);
    ui->frameRateSlider->setMinimum(1);
    ui->frameRateSlider->setValue(33);
}

// Called by GUI-timer
void Widget::updateGui()
{
    if( m_lastData )
    {
        m_videoVisualizer->setScan(m_lastData);
    }
}

void Widget::playDataFromFile()
{
    if( m_appCtrl->isPlaying() )
    {
        m_appCtrl->stopPlaying();
        ui->play_pushButton->setText("Play");
    }
    else
    {
        m_appCtrl->startPlaying();
        ui->frameRateSlider->setValue(33);
        ui->play_pushButton->setText("Stop");
    }
}

void Widget::setPlayRate()
{
    int playRate = ui->frameRateSlider->value();
    m_appCtrl->setPlayRate(playRate);
}

void Widget::updateFrameRate()
{
    long fps = static_cast<long>(1000.f * m_frameCount / FPS_LABEL_RATE );
    ui->frameRate_label->setText("FPS: " + QString::number(fps));
    m_frameCount = 0;
}
