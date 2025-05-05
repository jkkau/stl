#include "SharedPtr.hh"
#include <gtest/gtest.h>

TEST(SharedPtrTest, BasicCreationAndDestruction) {
    SharedPtr<int> p(new int(10));
    EXPECT_EQ(*p.get(), 10);
    EXPECT_EQ(p.use_count(), 1);
}

TEST(SharedPtrTest, CopyIncreasesRefCount) {
    SharedPtr<int> p1(new int(42));
    SharedPtr<int> p2 = p1;

    EXPECT_EQ(p1.get(), p2.get());
    EXPECT_EQ(*p2, 42);
    EXPECT_EQ(p1.use_count(), 2);
    EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtrTest, AssignmentIncreasesRefCount) {
    SharedPtr<int> p1(new int(100));
    SharedPtr<int> p2(new int(200));
    p2 = p1;

    EXPECT_EQ(p1.get(), p2.get());
    EXPECT_EQ(*p2, 100);
    EXPECT_EQ(p1.use_count(), 2);
    EXPECT_EQ(p2.use_count(), 2);
}

TEST(SharedPtrTest, DestructionDecreasesRefCount) {
    SharedPtr<int> p1(new int(5));
    {
        SharedPtr<int> p2 = p1;
        EXPECT_EQ(p1.use_count(), 2);
    }
    EXPECT_EQ(p1.use_count(), 1);
}
