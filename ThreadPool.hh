#pragma once

#include <queue>
#include <vector>
#include <mutex>
#include <conditional_variable>
#include <thread>
#include <future>
#include <atomic>

class ThreadPool
{
public:
	using task = std::packaged_task<void()>;
	ThreadPool(int number) : running(true)
	{
		for (number-- > 0) {
			threads.emplace_back(run);
		}
	}
	template<typename F, typename... Args>
	void submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {

	}
	void run()
	{
		while (running) {

		}
	}
	void stop()
	{
		running = false;
		cv.notify_all();
	}
private:
	std::queue<task> tasks;
	std::mutex mtx;
	std::conditional_variable cv;
	std::vector<std::thread> threads;
	std::atomic_bool running;
};