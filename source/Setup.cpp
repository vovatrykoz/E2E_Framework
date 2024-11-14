#include "Setup.h"

#include <iostream>

std::optional<setup::SupportedLogger> setup::getSupportedLoggerFromString(
    const std::string& loggerStr) {
    for (auto& c : loggerStr) {
        std::tolower(c);
    }

    if (loggerStr == "console") {
        return SupportedLogger::Console;
    }

    if (loggerStr == "text") {
        return SupportedLogger::Text;
    }

    return std::nullopt;
}

std::optional<setup::SupportedReader> setup::getSupportedReaderFromString(
    const std::string& readerStr) {
    for (auto& c : readerStr) {
        std::tolower(c);
    }

    if (readerStr == "console") {
        return SupportedReader::Console;
    }

    if (readerStr == "text") {
        return SupportedReader::Text;
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

        default:
            return nullptr;
    }

    return nullptr;
}

std::unique_ptr<IReader> setup::getReaderFromType(SupportedReader readerType) {
    std::string inputPath;
    switch (readerType) {
        case SupportedReader::Console:
            std::cout << "Reader type: console" << std::endl;
            return std::make_unique<InputReader>();

        case SupportedReader::Text:
            std::cout << "Reader type: text" << std::endl;
            std::cout << "Enter path to input file: ";
            std::cin >> inputPath;
            return std::make_unique<SimpleTextReader>(inputPath);

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

std::unique_ptr<IReader> setup::reader(const std::string& readerStr) {
    std::optional<setup::SupportedReader> readerType =
        setup::getSupportedReaderFromString(readerStr);

    if (!readerType.has_value()) {
        std::cerr << "Provided reader is not supported" << std::endl;
        return nullptr;
    }

    return setup::getReaderFromType(readerType.value());
}
