#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue
{
public:
    ConcurrentQueue();
    void push(T const& data);
    bool empty() const;
    bool try_pop(T& valPopped);
    void wait_and_pop(T& valPopped);
private:
    std::mutex mut;
    std::condition_variable cond;
    std::queue<T> queue;
};

#include "ConcurrentQueue.inl"