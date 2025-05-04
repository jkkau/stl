#include "Sort.hh"
#include <gtest/gtest.h>

TEST(SortTest, TestQSort) {
    int a[] = {5, 4, 3, 2, 1};
    int sortedA[] = {1, 2, 3, 4, 5};

    qsort(a, 5);
    EXPECT_EQ(sizeof(a), sizeof(sortedA));
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(a[i], sortedA[i]);
    }
}
