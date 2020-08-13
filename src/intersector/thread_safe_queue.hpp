#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <queue>

template <class T>
class ThreadSafeQueue {
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable cv;
    public:
        ThreadSafeQueue();
        void push(T val);
        T pop();
};

#endif