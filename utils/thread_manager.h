//
// Created by andrew on 2022/6/29.
//

#ifndef DLMS_THREAD_MANAGER_H
#define DLMS_THREAD_MANAGER_H
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>

typedef typename std::function<int32_t ()> Func;

class ThreadManager {
public:
    enum ThreadStatus {
        Initializing = 0,
        Running = 1,
        Stopping = 2,
    };

public:
    explicit ThreadManager(uint32_t threadNumber) {
        threadStatus = Initializing;
        this->Start(threadNumber);
    }
    ~ThreadManager() {
        Stop();
    }

    void Start(uint32_t threadNumber) {
        threadStatus = Running;
        for (uint32_t i = 0; i < threadNumber; i++) {
            this->threadPool.emplace_back(new std::thread(&ThreadManager::Run, this, i));
        }
    }

    void Dispatch(const Func& func) {
        std::unique_lock<std::mutex> lock(mux);
        queueFunc.push(func);
        lock.unlock();
        cv.notify_one();
    }
    // 在所有插件停止结束之后这里才能停止
    void Stop() {
        std::unique_lock<std::mutex> lock(mux);
        threadStatus = Stopping;
        lock.unlock();
        cv.notify_all();
        for (auto& dispatchThread : threadPool) {
            dispatchThread->join();
        }
    }

private:
    void Run(int32_t index) {
        std::string threadName = std::string("Worker-") + std::to_string(index);
        pthread_setname_np(threadPool[index]->native_handle(),threadName.c_str());

        std::unique_lock<std::mutex> lock(mux);
        while (Running == threadStatus) {
            cv.wait(lock, [&]{return (!queueFunc.empty() || Quit());});
            if (!Quit() && !queueFunc.empty()) {
                auto &op = queueFunc.front();
                queueFunc.pop();
                lock.unlock();
                op();
                lock.lock();
            }
        }
    }
    bool Quit() {
        return threadStatus != Running;
    }

private:
    std::vector<std::shared_ptr<std::thread>> threadPool{}; // 线程池
    ThreadStatus threadStatus{Initializing}; //
    std::mutex mux;
    std::queue<Func> queueFunc;
    std::condition_variable cv;
    std::atomic<bool> shouldContinue{};
};



#endif //DLMS_THREAD_MANAGER_H
