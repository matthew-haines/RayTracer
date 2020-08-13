#include "thread_safe_queue.hpp"

template <class T>
ThreadSafeQueue<T>::ThreadSafeQueue() {
    queue = std::queue<T>();
    mutex = std::mutex();
    cv = std::condition_variable();
}

template <class T>
void ThreadSafeQueue<T>::push(T val) {
    std::unique_lock<std::mutex> unique_lock(mutex);
    cv.wait(unique_lock);
    queue.push(val);
    unique_lock.unlock();
    cv.notify_one();
}

template <class T>
T ThreadSafeQueue<T>::pop() {
    std::unique_lock<std::mutex> unique_lock(mutex);
    cv.wait(unique_lock, [this]{return !queue.empty();});
    T result = queue.front();
    queue.pop();
    unique_lock.unlock();
    cv.notify_one();
    return result;
}