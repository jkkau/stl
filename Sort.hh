#pragma once

#include "ThreadPool.hh"
#include <algorithm>

template<typename T>
void qsortRecursive(T t[], int start, int end) {
    // printf("start: %d, end: %d\n", start, end);
    if (start >= end) {
        return;
    }
    int left = start;
    int right = end;
    int k = t[start];
    while (left < right) {
        while (t[left] < k && left < right) left++;
        while (t[right] > k && left < right) right--;
        std::swap(t[left], t[right]);
    }

    if (t[start] > t[left]) {
        // 将基准值和中间位置的值呼唤，达到中间位置左边的值都小于该值，右边位置的值都大于该值
        std::swap(t[start], t[left]);
    }

    qsortRecursive(t, start, left-1);
    // 这里需要注意是left+1而不是left，因为left这个位置已经确认了
    qsortRecursive(t, left+1, end);
}

template<typename T>
void qsort(T t[], int len) {
    qsortRecursive(t, 0, len-1);
}
