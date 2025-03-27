cmake_minimum_required(VERSION 3.20)
project(E2E_analysis_framework LANGUAGES C CXX)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if (MSVC)
    add_compile_options(/W4 /WX)
endif()

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CODE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

set(IO_LOGGER_SOURCE_DIR ${CODE_SOURCE_DIR}/io/logger)
set(IO_READER_SOURCE_DIR ${CODE_SOURCE_DIR}/io/reader)
add_library(
    e2e_io

    ${IO_LOGGER_SOURCE_DIR}/ConsoleColor.cpp
    ${IO_LOGGER_SOURCE_DIR}/ConsoleLogger.cpp
    ${IO_LOGGER_SOURCE_DIR}/ConsoleSystemLogger.cpp
    ${IO_LOGGER_SOURCE_DIR}/SimplifiedConsoleLogger.cpp
    ${IO_LOGGER_SOURCE_DIR}/TextLogger.cpp
    ${IO_LOGGER_SOURCE_DIR}/SimplifiedTextLogger.cpp

    ${IO_READER_SOURCE_DIR}/ConsoleTaskReader.cpp
    ${IO_READER_SOURCE_DIR}/SimpleTextTaskReader.cpp
    ${IO_READER_SOURCE_DIR}/TaskInstanceInputReader.cpp
    ${IO_READER_SOURCE_DIR}/TaskInstanceSimpleTextReader.cpp
)

add_library(
    e2e_core

    ${CODE_SOURCE_DIR}/PeriodicTask.cpp
    ${CODE_SOURCE_DIR}/TaskScheduling.cpp
    ${CODE_SOURCE_DIR}/Analysis.cpp
    ${CODE_SOURCE_DIR}/MathFramework.cpp
    ${CODE_SOURCE_DIR}/TimedPath.cpp
)

set(SETUP_SOURCE_DIR ${CODE_SOURCE_DIR}/setup)
add_library(
    e2e_setup

    ${SETUP_SOURCE_DIR}/Setup.cpp
    ${SETUP_SOURCE_DIR}/Preset.cpp
)

add_executable(
    individualPathAnalyzer

    ${CODE_SOURCE_DIR}/executable/main_IndividualPath.cpp
)

add_executable(
    taskAnalyzer
    
    ${CODE_SOURCE_DIR}/executable/main_Tasks.cpp
)

target_compile_features(individualPathAnalyzer PUBLIC cxx_std_20)
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

# Google Test ----------------------

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.16.0
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