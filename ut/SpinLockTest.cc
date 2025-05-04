#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include "SpinLock.hh"

TEST(SpinLockTest, ConcurrentIncrementIsCorrect) {
    int thread_count = 8;
    int increments_per_thread = 100000;

    int counter = 0;
    SpinLock lock;

    auto worker = [&]() {
        for (int i = 0; i < increments_per_thread; ++i) {
            lock.lock();
            ++counter;
            lock.unlock();
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(worker);
    }

    for (auto &t : threads) {
        t.join();
    }

    EXPECT_EQ(counter, thread_count * increments_per_thread);
}

TEST(TicketLockTest, ConcurrentIncrement) {
    TicketLock lock;
    int counter = 0;
    constexpr int thread_count = 10;
    constexpr int loop_count = 1000;

    auto worker = [&]() {
        for (int i = 0; i < loop_count; ++i) {
            lock.lock();
            ++counter;
            lock.unlock();
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(worker);
    }

    for (auto& t : threads) {
        t.join();
    }

    EXPECT_EQ(counter, thread_count * loop_count);
}