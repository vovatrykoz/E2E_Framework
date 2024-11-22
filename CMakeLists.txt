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
    textLogger
    ${CODE_SOURCE_DIR}/io/TextLogger.cpp
)

add_library(
    taskInstanceInputReader
    ${CODE_SOURCE_DIR}/io/TaskInstanceInputReader.cpp
)

add_library(
    taskInstanceSimpleTextReader
    ${CODE_SOURCE_DIR}/io/TaskInstanceSimpleTextReader.cpp
)

add_library(
    task
    ${CODE_SOURCE_DIR}/Task.cpp
)

add_library(
    setup
    ${CODE_SOURCE_DIR}/Setup.cpp
)

add_library(
    scheduling
    ${CODE_SOURCE_DIR}/TaskScheduling.cpp
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
    individualPathAnalyzer
    ${CODE_SOURCE_DIR}/executable/main_individualPath.cpp
)

target_compile_features(individualPathAnalyzer PUBLIC cxx_std_17)
target_link_libraries(taskInstanceInputReader timedPath)
target_link_libraries(consoleLogger timedPath)
target_link_libraries(taskInstanceSimpleTextReader timedPath)
target_link_libraries(textLogger timedPath)
target_link_libraries(
    setup 
    taskInstanceInputReader 
    consoleLogger 
    taskInstanceSimpleTextReader 
    textLogger
)

target_link_libraries(mathFramework task)
target_link_libraries(analysis mathFramework task)

target_link_libraries(
    individualPathAnalyzer 
    analysis
    setup
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
    mathFramework
    timedPath
    task
    analysis
    scheduling
)

include(GoogleTest)
gtest_discover_tests(testRunner)