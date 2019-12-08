/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "dataBuffer.h"

DataBuffer::DataBuffer(const uint& height, const uint& width )
{
    m_image = QImage(height, width, QImage::Format_RGB32);
}


