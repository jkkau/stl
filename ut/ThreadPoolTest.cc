#include "ThreadPool.hh"
#include <gtest/gtest.h>
#include <chrono>
#include <atomic>

TEST(ThreadPoolTest, SubmitAndGetResult)
{
	ThreadPool pool(4);
	auto future = pool.submit([] { return 42; });
	EXPECT_EQ(future.get(), 42);
}

TEST(ThreadPoolTest, MultipleTasks)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};
	for (int i = 0; i < 100; ++i) {
		pool.submit([&counter] { counter.fetch_add(1); });
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	EXPECT_EQ(counter.load(), 100);
}

TEST(ThreadPoolTest, StopGracefully)
{
	ThreadPool pool(2);
	for (int i = 0; i < 10; ++i) {
		pool.submit([] { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
	}
	pool.stop();
	SUCCEED();
}

