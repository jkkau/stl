#pragma once

// SpinLock和TicketLock都是不可重入锁, 重复加锁会造成死锁

#include <atomic>


class SpinLock {
public:
    SpinLock() = default;
    ~SpinLock() = default;

    void lock() {
        bool expect = false;

        // 通过memory_order_acquire来保证顺序性, memory_order_acquire后面的代码都在前后执行，以达到加锁的目的
        while (!flag.compare_exchange_weak(expect, true, std::memory_order_acquire)) {
            expect = false;
            std::this_thread::yield();
        }
    }
    void unlock() {
        // memory_order_release保证unlock之前的操作都在memory_order_release之前发生
        // 其他线程看到unlock则能看到unlock之前的操作
        // memory_order_release与lock中的memory_order_acquire保证被加锁的数据的顺序性
        flag.store(false, std::memory_order_release);
    }
private:
    std::atomic<bool> flag{false};
};


// A FIFO spin lock
class TicketLock {
public:
    TicketLock() = default;
    ~TicketLock() = default;

    void lock() {
        // fetch_add将ticket加1并返回加一前的值
        uint32_t my_ticket = ticket.fetch_add(1, std::memory_order_relaxed);

        // 每个线程拿到自己的票号后
        while (serving.load(std::memory_order_acquire) != my_ticket) {
            std::this_thread::yield();
        }
    }
    void unlock() {
        serving.fetch_add(1, std::memory_order_release);
    }
private:
    std::atomic<uint32_t> ticket{0};
    std::atomic<uint32_t> serving{0};
};