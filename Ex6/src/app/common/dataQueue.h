/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef DATAQUEUE
#define DATAQUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include "dataBuffer.h"


/**
 * A thread save data queue implementation ( producer-consumer queue ) using 1 conditional variable
 *
 *
 * @author Patrik Arnold
 */
template<class T>
class DataQueue
{
    std::condition_variable m_cond;
    std::mutex m_mutex;
    std::queue<T> m_dataQueue;
    size_t m_maxSize;
public:
    DataQueue(int mxsz = 1000) : m_maxSize(mxsz)
    { }

    /**
     * @brief add: Add an element to the queue
     * @param element
     */
    void add(T element)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]()
        { return !isFull(); });
        m_dataQueue.push(element);
        lock.unlock();
        m_cond.notify_all();
    }

    /**
     * @brief get: Get an element from the queue
     * @param element
     */
    void get(T &element)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this]()
        { return !isEmpty(); });
        element = m_dataQueue.front();
        m_dataQueue.pop();
        lock.unlock();
        m_cond.notify_all();

    }

    bool isFull() const
    {
        return m_dataQueue.size() >= m_maxSize;
    }

    bool isEmpty() const
    {
        return m_dataQueue.size() == 0;
    }

    int length() const
    {
        return m_dataQueue.size();
    }

    void clear()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (!isEmpty())
        {
            m_dataQueue.pop();
        }
        lock.unlock();
        m_cond.notify_all();
    }
};

#endif // DATAQUEUE

