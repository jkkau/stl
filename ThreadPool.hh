#pragma once

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>
#include <atomic>
#include <memory>
#include <functional>

class ThreadPool
{
public:
	ThreadPool(int number) : running(true) {
		while (number-- > 0) {
			threads.emplace_back([this]() {this->run();});
		}
	}
	~ThreadPool() {
		if (running) {
			stop();
		}
	}

	template<typename F, typename... Args>
	auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
		using RetType = decltype(f(args...));
		auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		auto task = std::make_shared<std::packaged_task<RetType ()>>(bound);
		{
			std::lock_guard lk(mtx);

			// [task]按值捕获, 智能指针引用计数+1
			// *task()执行operator()()，即执行packaged_task对应的函数
			tasks.emplace([task]() {(*task)();});
		}
		cv.notify_one();

		return task->get_future();
	}
	void run() {
		while (running) {
			std::function<void()> task;
			{
				std::unique_lock lk(mtx);
				while (tasks.empty() && running) {
					cv.wait(lk);
				}
				if (not running) {
					return;
				}
				task = std::move(tasks.front());
				tasks.pop();
			}
			task();
		}
	}
	void stop() {
		running = false;
		cv.notify_all();
		for (auto &t : threads) {
			if (t.joinable()) {
				t.join();
			}
		}
	}
private:
	std::queue<std::function<void()>> tasks;
	std::mutex mtx;
	std::condition_variable cv;
	std::vector<std::thread> threads;
	std::atomic_bool running;
};