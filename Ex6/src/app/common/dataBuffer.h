/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <memory>
#include <QImage>
/**
 * This class is the container for one data buffer. Modify content as required
 *
 * @author Patrik Arnold
 */
class DataBuffer
{
public:

    /**
     * Constructor for the data container. Several buffers are
     * pre-initialized following to the passed parameters.
     *
     * @param height
     * @param width
     */
    DataBuffer(const uint& height, const uint& width );

public:
    QImage m_image;   
};

typedef std::shared_ptr<DataBuffer> DataBufferPtr;

#endif // DATABUFFER_H
