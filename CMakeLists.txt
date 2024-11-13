cmake_minimum_required(VERSION 3.20)
project(E2E_analysis_framework LANGUAGES C CXX)

cmake_policy(SET CMP0135 NEW)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CODE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

add_executable(
    runner
    ${CODE_SOURCE_DIR}/main.cpp
)

target_compile_features(runner PUBLIC cxx_std_17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    testRunner
    ${TESTS_SOURCE_DIR}/TemporaryTest.cpp
)

target_link_libraries(
    testRunner
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testRunner)