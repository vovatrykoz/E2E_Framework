cmake_minimum_required(VERSION 3.20)
project(E2E_analysis_framework LANGUAGES C CXX)

cmake_policy(SET CMP0135 NEW)

set (CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CODE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

add_library(
    consoleLogger
    ${CODE_SOURCE_DIR}/io/ConsoleLogger.cpp
)

add_library(
    inputReader
    ${CODE_SOURCE_DIR}/io/InputReader.cpp
)

add_library(
    simpleTextReader
    ${CODE_SOURCE_DIR}/io/SimpleTextReader.cpp
)

add_library(
    task
    ${CODE_SOURCE_DIR}/Task.cpp
)

add_library(
    analysis
    ${CODE_SOURCE_DIR}/Analysis.cpp
)

add_library(
    mathFramework
    ${CODE_SOURCE_DIR}/MathFramework.cpp
)

add_library(
    timedPath
    ${CODE_SOURCE_DIR}/TimedPath.cpp
)

add_executable(
    runner
    ${CODE_SOURCE_DIR}/main.cpp
)

target_compile_features(runner PUBLIC cxx_std_17)
target_link_libraries(inputReader timedPath)
target_link_libraries(consoleLogger timedPath)
target_link_libraries(simpleTextReader timedPath)
target_link_libraries(mathFramework task)
target_link_libraries(runner analysis task mathFramework timedPath consoleLogger inputReader simpleTextReader)

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
    ${TESTS_SOURCE_DIR}/AnalysisTests.cpp
    ${TESTS_SOURCE_DIR}/MathFrameworkTests.cpp
    ${TESTS_SOURCE_DIR}/TimedPathTests.cpp
)

target_link_libraries(
    testRunner
    GTest::gtest_main
    mathFramework
    timedPath
    task
    analysis
)

include(GoogleTest)
gtest_discover_tests(testRunner)