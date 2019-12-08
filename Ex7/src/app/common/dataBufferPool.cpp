/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <iostream>
#include "dataBufferPool.h"

DataBufferPool::DataBufferPool(const uint& height, const uint& width) :
    m_height(height),
    m_width(width),
    m_initialBufferSize(10)
{
    for( uint i = 0; i < m_initialBufferSize; i++ )
        extendPool();
}

DataBufferPtr DataBufferPool::extendPool()
{
    DataBufferPtr tmp( new DataBuffer(m_height, m_width) );
    m_pool.push_back( tmp );
    return tmp;
}

DataBufferPtr DataBufferPool::getBuffer()
{
    // mutex unlock done automaticaly when leaving this function scope
    std::lock_guard<std::mutex> lock(m_poolLock);

    // look for an unused buffer in the pool
    for( uint i = 0; i < m_pool.size(); i++ )
    {
        if( m_pool.at(i).use_count() == 1 )
            return m_pool.at(i);
    }

    // allocate a new buffer in the pool if no existing buffer is available
    DataBufferPtr newBuffer = extendPool();
    std::cout << "Warning: DataPool::GetBuffer() allocates buffer " << m_pool.size() << std::endl;

    return newBuffer;
}
