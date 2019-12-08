/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef DATABUFFERPOOL_H
#define DATABUFFERPOOL_H

#include <memory>
#include <vector>
#include <mutex>

#include "dataBuffer.h"

/**
 * This class holds a specific number of smart-pointers to initialized DataBuffer
 * objects. Users can request a next DataBuffer and get a
 * DataBuffer object which is currently unused. If all DataBuffer
 * are in use, a new one is created and added to the pool of buffers.
 */
class DataBufferPool
{
public:

    DataBufferPool(const uint& height, const uint& width );

    /**
     * Get an unsued DataBuffer object.
     *
     * @return A smart-pointer to an unused DataBuffer object.
     */
    DataBufferPtr getBuffer();


private:
    DataBufferPtr extendPool();

    std::vector<DataBufferPtr> m_pool;
    const uint m_height;
    const uint m_width;
    uint m_initialBufferSize;
    std::mutex m_poolLock;
};


#endif // DATABUFFERPOOL_H
