#include "ConcurrentQueue.h"

template <typename T>
ConcurrentQueue<T>::ConcurrentQueue()
{
    // empty
}

template <typename T>
void ConcurrentQueue<T>::pushBack(T const& data)
{
    std::lock_guard<std::mutex> lock(mut);
    queue.push_back(data);
    cond.notify_one();
}

template <typename T>
bool ConcurrentQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(mut);
    return queue.empty();
}

template <typename T>
bool ConcurrentQueue<T>::tryPopFront(T& valPopped)
{
    std::lock_guard<std::mutex> lock(mut);
    if (queue.empty())
        return false;
    valPopped = queue.front();
    queue.pop_front();
    return true;
}

template <typename T>
void ConcurrentQueue<T>::waitPopFront(T& valPopped)
{
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [this] {return !queue.empty(); });
    valPopped = queue.front();
    queue.pop_front();
}

template <typename T>
void ConcurrentQueue<T>::waitPopBack(T& valPopped)
{
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [this] {return !queue.empty(); });
    valPopped = queue.back();
    queue.pop_back();
}

template<typename T>
std::deque<T>::size_type ConcurrentQueue<T>::size() const
{
    std::lock_guard<std::mutex> lock(mut);
    return this->queue.size();
}