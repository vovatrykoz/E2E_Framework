cmake_minimum_required(VERSION 3.20)
project(E2E_analysis_framework LANGUAGES C CXX)

cmake_policy(SET CMP0135 NEW)

set (CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CODE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})


add_library(
    e2e_io

    ${CODE_SOURCE_DIR}/io/ConsoleLogger.cpp
    ${CODE_SOURCE_DIR}/io/ConsoleTaskReader.cpp
    ${CODE_SOURCE_DIR}/io/SimpleTextTaskReader.cpp
    ${CODE_SOURCE_DIR}/io/TextLogger.cpp
    ${CODE_SOURCE_DIR}/io/TaskInstanceInputReader.cpp
    ${CODE_SOURCE_DIR}/io/TaskInstanceSimpleTextReader.cpp
)

add_library(
    e2e_core

    ${CODE_SOURCE_DIR}/Task.cpp
    ${CODE_SOURCE_DIR}/TaskScheduling.cpp
    ${CODE_SOURCE_DIR}/Analysis.cpp
    ${CODE_SOURCE_DIR}/MathFramework.cpp
    ${CODE_SOURCE_DIR}/TimedPath.cpp
)

add_library(
    e2e_setup

    ${CODE_SOURCE_DIR}/Setup.cpp
)

add_executable(
    individualPathAnalyzer

    ${CODE_SOURCE_DIR}/executable/main_IndividualPath.cpp
)

add_executable(
    taskAnalyzer
    
    ${CODE_SOURCE_DIR}/executable/main_Tasks.cpp
)

target_compile_features(individualPathAnalyzer PUBLIC cxx_std_17)
target_link_libraries(e2e_io e2e_core)
target_link_libraries(
    e2e_setup 
    e2e_io
)

target_link_libraries(
    individualPathAnalyzer 
    e2e_core
    e2e_setup
)

target_link_libraries(
    taskAnalyzer 
    e2e_core
    e2e_setup
)

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
    ${TESTS_SOURCE_DIR}/TaskSchedulingTests.cpp
    ${TESTS_SOURCE_DIR}/TimedPathTests.cpp
)

target_link_libraries(
    testRunner
    GTest::gtest_main
    e2e_core
)

include(GoogleTest)
gtest_discover_tests(testRunner)