#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue
{
public:
    explicit ConcurrentQueue();
    void pushBack(T const& data);
    bool empty() const;
    bool tryPopFront(T& valPopped);
    void waitPopFront(T& valPopped);
    void waitPopBack(T& valPopped);
    std::deque<T>::size_type size() const;
private:
    mutable std::mutex mut;
    std::condition_variable cond;
    std::deque<T> queue;
};

#include "ConcurrentQueue.inl"