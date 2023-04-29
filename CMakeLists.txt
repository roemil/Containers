cmake_minimum_required(VERSION 3.14)
project(codec)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(array/include)
include_directories(vector/include)

add_executable(
    container_SUITE
    vector/vectorTest.cpp
    vector/SmartVectorTest.cpp
    array/arrayTest.cpp
    TestMain.cpp
)
target_link_libraries(
    container_SUITE gtest_main
)
 
include(GoogleTest)
gtest_discover_tests(container_SUITE)