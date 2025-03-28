#include <e2e/io/logger/ConsoleLogger.h>
#include <e2e/io/logger/PlainTextLogger.h>
#include <e2e/io/logger/SimplifiedConsoleLogger.h>
#include <e2e/io/logger/SimplifiedPlainTextLogger.h>
#include <e2e/io/reader/ConsoleTaskInstanceReader.h>
#include <e2e/io/reader/ConsoleTaskReader.h>
#include <e2e/io/reader/PlainTextTaskInstanceReader.h>
#include <e2e/io/reader/PlainTextTaskReader.h>
#include <e2e/setup/Factory.h>
#include <e2e/setup/Setup.h>

#include <algorithm>
#include <iostream>

using namespace e2e;
using namespace e2e::io;

std::unique_ptr<IResultLogger> setup::logger(const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
        std::back_inserter(lowercaseLoggerStr), [](unsigned char c) {
            return static_cast<unsigned char>(
                std::tolower(static_cast<int>(c)));
        });

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
    const std::string& loggerStr, const ISystemLogger* systemLogger) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(),
        std::back_inserter(lowercaseLoggerStr), [](unsigned char c) {
            return static_cast<unsigned char>(
                std::tolower(static_cast<int>(c)));
        });

    if (lowercaseLoggerStr == "console") {
        systemLogger->logInfo("Logger type: console");
        return factory::makeLogger<SimplifiedConsoleLogger>();
    }

    if (lowercaseLoggerStr == "text") {
        systemLogger->logInfo("Logger type: text");
        systemLogger->logMessage("Enter output path: ");
        const std::string outputPath = []() {
            std::string userInput;
            std::cin >> userInput;
            return userInput;
            }();
        return factory::makeLogger<SimplifiedPlainTextLogger>(outputPath);
    }

    systemLogger->logError("Entered logger is not supported: \"" + loggerStr +
        "\"");
    return nullptr;
}

std::unique_ptr<ITaskInstanceReader> setup::taskInstanceReader(
    const std::string& readerStr) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(),
        std::back_inserter(lowercaseReaderStr), [](unsigned char c) {
            return static_cast<unsigned char>(
                std::tolower(static_cast<int>(c)));
        });

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
    const std::string& readerStr, const std::string& filePath,
    const ISystemLogger* systemLogger) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(),
        std::back_inserter(lowercaseReaderStr), [](unsigned char c) {
            return static_cast<unsigned char>(
                std::tolower(static_cast<int>(c)));
        });

    if (lowercaseReaderStr == "console") {
        systemLogger->logInfo("Reader type: console");

        if (filePath != "") {
            systemLogger->logWarning(
                "Console reader is chosen! Discarding the provided file path");
        }

        return factory::makeTaskReader<ConsoleTaskReader>();
    }

    if (lowercaseReaderStr == "text") {
        systemLogger->logInfo("Reader type: text");
        return factory::makeTaskReader<PlainTextTaskReader>(filePath);
    }

    systemLogger->logError("Entered task reader is not supported: \"" +
        readerStr + "\"");
    return nullptr;
}
