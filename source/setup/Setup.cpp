#include <io/logger/ConsoleLogger.h>
#include <io/logger/PlainTextLogger.h>
#include <io/logger/SimplifiedConsoleLogger.h>
#include <io/logger/SimplifiedPlainTextLogger.h>
#include <io/reader/ConsoleTaskInstanceReader.h>
#include <io/reader/ConsoleTaskReader.h>
#include <io/reader/PlainTextTaskInstanceReader.h>
#include <io/reader/PlainTextTaskReader.h>
#include <setup/Factory.h>
#include <setup/Setup.h>

#include <algorithm>
#include <iostream>

using namespace e2e;
using namespace e2e::io;

std::unique_ptr<IResultLogger> setup::logger(const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
                   std::back_inserter(lowercaseLoggerStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseLoggerStr == "console") {
        std::cout << "Logger type: console" << std::endl;
        return factory::makeLogger<ConsoleLogger>();
    }

    if (lowercaseLoggerStr == "text") {
        std::string outputPath;
        std::cout << "Logger type: text" << std::endl;
        std::cout << "Enter output path: ";
        std::cin >> outputPath;
        return factory::makeLogger<PlainTextLogger>(outputPath);
    }

    return nullptr;
}

std::unique_ptr<IResultLogger> setup::simpleLogger(
    const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
                   std::back_inserter(lowercaseLoggerStr),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercaseLoggerStr == "console") {
        std::cout << "Logger type: console" << std::endl;
        return factory::makeLogger<SimplifiedConsoleLogger>();
    }

    if (lowercaseLoggerStr == "text") {
        std::string outputPath;
        std::cout << "Logger type: text" << std::endl;
        std::cout << "Enter output path: ";
        std::cin >> outputPath;
        return factory::makeLogger<SimplifiedPlainTextLogger>(outputPath);
    }

    std::cout << "Entered logger is not supported" << std::endl;
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
        return factory::makeTaskInstanceReader<ConsoleTaskInstanceReader>();
    }

    if (lowercaseReaderStr == "text") {
        std::string inputPath;
        std::cout << "Reader type: text" << std::endl;
        std::cout << "Enter path to input file: ";
        std::cin >> inputPath;
        return factory::makeTaskInstanceReader<PlainTextTaskInstanceReader>(
            inputPath);
    }

    std::cout << "Entered task instance reader is not supported" << std::endl;
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
        return factory::makeTaskReader<ConsoleTaskReader>();
    }

    if (lowercaseReaderStr == "text") {
        std::string inputPath;
        std::cout << "Reader type: text" << std::endl;
        std::cout << "Enter path to input file: ";
        std::cin >> inputPath;
        return factory::makeTaskReader<PlainTextTaskReader>(inputPath);
    }

    std::cout << "Entered task reader is not supported" << std::endl;
    return nullptr;
}
