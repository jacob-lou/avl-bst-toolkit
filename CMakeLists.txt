cmake_minimum_required(VERSION 3.16)
project(cpp_avl_bst_toolkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- demos ----
add_executable(demo_bst bst-test.cpp)
target_include_directories(demo_bst PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(demo_equalpaths equal-paths.cpp equal-paths-test.cpp)
target_include_directories(demo_equalpaths PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ---- GoogleTest ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_hw4
  tests/test_avl.cpp
  tests/test_equalpaths.cpp
)
target_include_directories(test_hw4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_hw4 PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_hw4)
