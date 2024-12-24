#include <setup/Setup.h>

#include <io/logger/ConsoleLogger.h>
#include <io/logger/SimplifiedConsoleLogger.h>
#include <io/logger/SimplifiedTextLogger.h>
#include <io/logger/TextLogger.h>
#include <io/reader/ConsoleTaskReader.h>
#include <io/reader/SimpleTextTaskReader.h>
#include <io/reader/TaskInstanceInputReader.h>
#include <io/reader/TaskInstanceSimpleTextReader.h>

#include <algorithm>
#include <iostream>

using namespace e2e;
using namespace e2e::io;

std::unique_ptr<ILogger> setup::logger(const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
                   std::back_inserter(lowercaseLoggerStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseLoggerStr == "console") {
        std::cout << "Logger type: console" << std::endl;
        return makeLogger<ConsoleLogger>();
    }

    if (lowercaseLoggerStr == "text") {
        std::string outputPath;
        std::cout << "Logger type: text" << std::endl;
        std::cout << "Enter output path: ";
        std::cin >> outputPath;
        return makeLogger<TextLogger>(outputPath);
    }

    return nullptr;
}

std::unique_ptr<ILogger> setup::simpleLogger(const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
                   std::back_inserter(lowercaseLoggerStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseLoggerStr == "console") {
        std::cout << "Logger type: console" << std::endl;
        return makeLogger<SimplifiedConsoleLogger>();
    }

    if (lowercaseLoggerStr == "text") {
        std::string outputPath;
        std::cout << "Logger type: text" << std::endl;
        std::cout << "Enter output path: ";
        std::cin >> outputPath;
        return makeLogger<SimplifiedTextLogger>(outputPath);
    }

    return nullptr;
}

std::unique_ptr<ITaskInstanceReader> setup::taskInstanceReader(
    const std::string& readerStr) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(),
                   std::back_inserter(lowercaseReaderStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseReaderStr == "console") {
        std::cout << "Reader type: console" << std::endl;
        return makeTaskInstanceReader<TaskInstanceInputReader>();
    }

    if (lowercaseReaderStr == "text") {
        std::string inputPath;
        std::cout << "Reader type: text" << std::endl;
        std::cout << "Enter path to input file: ";
        std::cin >> inputPath;
        return makeTaskInstanceReader<TaskInstanceSimpleTextReader>(inputPath);
    }

    return nullptr;
}

std::unique_ptr<ITaskReader> e2e::setup::taskReader(
    const std::string& readerStr) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(),
                   std::back_inserter(lowercaseReaderStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseReaderStr == "console") {
        std::cout << "Reader type: console" << std::endl;
        return makeTaskReader<ConsoleTaskReader>();
    }

    if (lowercaseReaderStr == "text") {
        std::string inputPath;
        std::cout << "Reader type: text" << std::endl;
        std::cout << "Enter path to input file: ";
        std::cin >> inputPath;
        return makeTaskReader<SimpleTextTaskReader>(inputPath);
    }

    return nullptr;
}
