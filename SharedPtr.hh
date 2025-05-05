#pragma once
#include <cstdint>

struct PtrCounter {
    PtrCounter(uint32_t c) : count(c) {
    }
    uint32_t count;
};

template<typename T>
class SharedPtr {
public:
    SharedPtr(T *ele) : t(ele) {
        counter = new PtrCounter(1);
    }
    SharedPtr(const SharedPtr& s) {
        counter = s.counter;
        counter->count++;
        t = s.t;
    }
    SharedPtr& operator=(const SharedPtr& s) {
        if (this == &s) {
            return *this;
        }
        // 先对被赋值的SharedPtr做一次release
        release();
        counter = s.counter;
        counter->count++;
        t = s.t;

        return *this;
    }
    T operator*() {
        return *t;
    }
    uint32_t use_count() const {
        return counter->count;
    }
    T *get() {
        return t;
    }
    ~SharedPtr() {
        release();
    }

private:
    void release() {
        if (--counter->count == 0) {
            delete t;
            delete counter;
            t = nullptr;
            counter = nullptr;
        }
    }

private:
    T *t;
    PtrCounter *counter;
};