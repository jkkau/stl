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
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable benchmark tests")
FetchContent_MakeAvailable(benchmark)

enable_testing()

# 单元测试
add_executable(stl ThreadPoolTest.cc)
target_include_directories(stl PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(stl gtest_main)
include(GoogleTest)
gtest_discover_tests(stl)

# Benchmark 测试
add_executable(stl_benchmark ThreadPoolBenchmark.cpp)
target_include_directories(stl_benchmark PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(stl_benchmark benchmark::benchmark)
