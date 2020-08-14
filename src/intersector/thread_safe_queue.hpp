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
        ThreadSafeQueue() {};
        void push(T val) {
            std::unique_lock<std::mutex> unique_lock(mutex);
            queue.push(val);
            unique_lock.unlock();
            cv.notify_one();
        }
        T pop() {
            std::unique_lock<std::mutex> unique_lock(mutex);
            cv.wait(unique_lock, [this]{return !queue.empty();});
            T result = queue.front();
            queue.pop();
            unique_lock.unlock();
            cv.notify_one();
            return result;
        }
};

#endif