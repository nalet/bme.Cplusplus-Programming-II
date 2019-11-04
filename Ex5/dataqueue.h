#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <thread>
#include <future>
#include <queue>

template <typename T>
class DataQueue
{
private:
    std::deque<T> q;
    std::mutex mu_get;
    std::mutex mu_add;
    std::condition_variable cv_add;
    std::condition_variable cv_get;
    unsigned long max_buffer_size{1000};
    unsigned long buffer_size{0};
public:
    DataQueue(unsigned long max_buffer_size = 1000) : max_buffer_size(max_buffer_size) { }

    void add(T item)
    {
        std::unique_lock<std::mutex> locker{this->mu_add};
        this->cv_get.wait(locker, [this] {return !this->isFull();});
        this->q.push_front(item);
        ++this->buffer_size;
        locker.unlock();
        this->cv_add.notify_all();
    }

    T get()
    {
        std::unique_lock<std::mutex> locker{this->mu_get};
        this->cv_add.wait(locker, [this] {return !this->isEmpty();});
        T item = q.back();
        this->q.pop_back();
        --this->buffer_size;
        locker.unlock();
        this->cv_get.notify_one();
        return item;
    }

    bool isEmpty()
    {
        return this->buffer_size == 0;
    }

    bool isFull()
    {
        return this->buffer_size == this->max_buffer_size;
    }
};

#endif // DATAQUEUE_H
