cmake_minimum_required(VERSION 3.14)
project(stl)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Fetch Google Benchmark
# FetchContent_Declare(
#   benchmark
#   URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
# )
# set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable benchmark tests")
# FetchContent_MakeAvailable(benchmark)

# 单元测试
set(TEST_SOURCES
    TestMain.cc
    ThreadPoolTest.cc
    SortTest.cc
    SpinLockTest.cc
)

add_executable(ut ${TEST_SOURCES})
target_include_directories(ut PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(ut gtest_main)
include(GoogleTest)

# Benchmark 测试
#add_executable(stl_benchmark ThreadPoolBenchmark.cc)
#target_include_directories(stl_benchmark PRIVATE ${CMAKE_SOURCE_DIR})
#target_link_libraries(stl_benchmark benchmark::benchmark)
