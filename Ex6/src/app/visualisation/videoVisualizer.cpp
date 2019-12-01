/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "videoVisualizer.h"
#include "rOg_image.h"
#include <QLabel>
#include <QVBoxLayout>

// Constructor
VideoVisualizer::VideoVisualizer( QWidget* parent ) : QWidget( parent ), m_firstFrame(true)
{
    // Create the image widget
    m_imgWidget.reset( new rOg_image(parent));
    m_layout.reset( new QVBoxLayout( parent ));

    QImage dummy(256,256,QImage::Format_RGB32);
    m_image = dummy;
    for (int x = 0; x < 256; x ++)
    {
        for (int y =0; y < 256; y++)
        {
            m_image.setPixel( x, y, qRgb(x,x,x) );
        }
    }
    // Draw the Qt image in the image widget
    m_imgWidget->setImage(m_image);
    m_layout->addWidget( m_imgWidget.get() );
    setLayout( m_layout.get() );
}

VideoVisualizer::~VideoVisualizer()
{

}

void VideoVisualizer::setScan(DataBufferPtr data)
{
    if( !data )
        return;

    m_image = data->m_image;
    redrawFrame();
}

void VideoVisualizer::redrawFrame()
{
    QSize theParentSize = reinterpret_cast<QWidget*>(this->parent())->size();
    QImage scaleImg = m_image.scaled( theParentSize.width(), theParentSize.height() );
    m_imgWidget->setImage(scaleImg);

    if(m_firstFrame)
    {
        m_imgWidget->fitImage();
        m_firstFrame = false;
    }

    this->resize( theParentSize.width(), theParentSize.height() );
}
