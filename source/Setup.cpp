#include "Setup.h"

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

std::optional<setup::SupportedLogger> setup::getSupportedLoggerFromString(
    const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(), std::back_inserter(lowercaseLoggerStr), [](unsigned char c) {
        return std::tolower(c);
    });

    if (lowercaseLoggerStr == "console") {
        return SupportedLogger::Console;
    }

    if (lowercaseLoggerStr == "text") {
        return SupportedLogger::Text;
    }

    return std::nullopt;
}

std::optional<setup::SupportedLogger> setup::getSupportedSimpleLoggerFromString(
    const std::string& loggerStr) {
    std::string lowercaseLoggerStr;
    std::transform(loggerStr.begin(), loggerStr.end(), std::back_inserter(lowercaseLoggerStr), [](unsigned char c) {
        return std::tolower(c);
    });

    if (lowercaseLoggerStr == "console") {
        return SupportedLogger::SimplifiedConsole;
    }

    if (lowercaseLoggerStr == "text") {
        return SupportedLogger::SimplifiedText;
    }

    return std::nullopt;
}

std::optional<setup::SupportedTaskInstanceReader>
setup::getSupportedTaskInstanceReaderFromString(const std::string& readerStr) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(), std::back_inserter(lowercaseReaderStr), [](unsigned char c) {
        return std::tolower(c);
    });

    if (lowercaseReaderStr == "console") {
        return SupportedTaskInstanceReader::Console;
    }

    if (lowercaseReaderStr == "text") {
        return SupportedTaskInstanceReader::Text;
    }

    return std::nullopt;
}

std::optional<setup::SupportedTaskReader>
setup::getSupportedTaskReaderFromString(const std::string& readerStr) {
    std::string lowercaseReaderStr;
    std::transform(readerStr.begin(), readerStr.end(), std::back_inserter(lowercaseReaderStr), [](unsigned char c) {
        return std::tolower(c);
    });

    if (lowercaseReaderStr == "console") {
        return SupportedTaskReader::Console;
    }

    if (lowercaseReaderStr == "text") {
        return SupportedTaskReader::Text;
    }

    return std::nullopt;
}

std::unique_ptr<ILogger> setup::getLoggerFromType(SupportedLogger loggerType) {
    std::string outputPath;
    switch (loggerType) {
        case SupportedLogger::Console:
            std::cout << "Logger type: console" << std::endl;
            return std::make_unique<ConsoleLogger>();

        case SupportedLogger::Text:
            std::cout << "Logger type: text" << std::endl;
            std::cout << "Enter output path: ";
            std::cin >> outputPath;
            return std::make_unique<TextLogger>(outputPath);

        case SupportedLogger::SimplifiedConsole:
            std::cout << "Logger type: console" << std::endl;
            return std::make_unique<SimplifiedConsoleLogger>();

        case SupportedLogger::SimplifiedText:
            std::cout << "Logger type: text" << std::endl;
            std::cout << "Enter output path: ";
            std::cin >> outputPath;
            return std::make_unique<SimplifiedTextLogger>(outputPath);

        default:
            return nullptr;
    }

    return nullptr;
}

std::unique_ptr<ITaskInstanceReader> setup::getTaskInstanceReaderFromType(
    SupportedTaskInstanceReader readerType) {
    std::string inputPath;
    switch (readerType) {
        case SupportedTaskInstanceReader::Console:
            std::cout << "Reader type: console" << std::endl;
            return std::make_unique<TaskInstanceInputReader>();

        case SupportedTaskInstanceReader::Text:
            std::cout << "Reader type: text" << std::endl;
            std::cout << "Enter path to input file: ";
            std::cin >> inputPath;
            return std::make_unique<TaskInstanceSimpleTextReader>(inputPath);

        default:
            return nullptr;
    }

    return nullptr;
}

std::unique_ptr<ITaskReader> e2e::setup::getTaskReaderFromType(
    SupportedTaskReader readerType) {
    std::string inputPath;
    switch (readerType) {
        case SupportedTaskReader::Console:
            std::cout << "Reader type: console" << std::endl;
            return std::make_unique<ConsoleTaskReader>();

        case SupportedTaskReader::Text:
            std::cout << "Reader type: text" << std::endl;
            std::cout << "Enter path to input file: ";
            std::cin >> inputPath;
            return std::make_unique<SimpleTextTaskReader>(inputPath);

        default:
            return nullptr;
    }

    return nullptr;
}

std::unique_ptr<ILogger> setup::logger(const std::string& loggerStr) {
    std::optional<setup::SupportedLogger> loggerType =
        setup::getSupportedLoggerFromString(loggerStr);

    if (!loggerType.has_value()) {
        std::cerr << "Provided reader is not supported" << std::endl;
        return nullptr;
    }

    return setup::getLoggerFromType(loggerType.value());
}

std::unique_ptr<ILogger> setup::simpleLogger(const std::string& loggerStr) {
    std::optional<setup::SupportedLogger> loggerType =
        setup::getSupportedSimpleLoggerFromString(loggerStr);

    if (!loggerType.has_value()) {
        std::cerr << "Provided reader is not supported" << std::endl;
        return nullptr;
    }

    return setup::getLoggerFromType(loggerType.value());
}

std::unique_ptr<ITaskInstanceReader> setup::taskInstanceReader(
    const std::string& readerStr) {
    std::optional<setup::SupportedTaskInstanceReader> readerType =
        setup::getSupportedTaskInstanceReaderFromString(readerStr);

    if (!readerType.has_value()) {
        std::cerr << "Provided reader is not supported" << std::endl;
        return nullptr;
    }

    return setup::getTaskInstanceReaderFromType(readerType.value());
}

std::unique_ptr<ITaskReader> e2e::setup::taskReader(
    const std::string& readerStr) {
    std::optional<setup::SupportedTaskReader> readerType =
        setup::getSupportedTaskReaderFromString(readerStr);

    if (!readerType.has_value()) {
        std::cerr << "Provided reader is not supported" << std::endl;
        return nullptr;
    }

    return setup::getTaskReaderFromType(readerType.value());
}
