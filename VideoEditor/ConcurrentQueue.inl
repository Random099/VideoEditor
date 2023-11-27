#include "ConcurrentQueue.h"

template <typename T>
ConcurrentQueue<T>::ConcurrentQueue()
{
    // empty
}

template <typename T>
void ConcurrentQueue<T>::push(T const& data)
{
    std::lock_guard<std::mutex> lock(mut);
    queue.push(data);
    cond.notify_one();
}

template <typename T>
bool ConcurrentQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(mut);
    return queue.empty();
}

template <typename T>
bool ConcurrentQueue<T>::try_pop(T& valPopped)
{
    std::lock_guard<std::mutex> lock(mut);
    if (queue.empty())
        return false;
    valPopped = queue.front();
    queue.pop();
    return true;
}

template <typename T>
void ConcurrentQueue<T>::wait_and_pop(T& valPopped)
{
    std::unique_lock<std::mutex> lock(mut);
    cond.wait(lock, [this] {return !queue.empty(); });
    valPopped = queue.front();
    queue.pop();
}

template<typename T>
std::queue<T>::size_type ConcurrentQueue<T>::size() const
{
    std::lock_guard<std::mutex> lock(mut);
    return this->queue.size();
}