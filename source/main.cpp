#include <Analysis.h>
#include <io/ConsoleLogger.h>
#include <io/InputReader.h>
#include <io/SimpleTextReader.h>
#include <io/TextLogger.h>

#include <iostream>
#include <memory>
#include <optional>

enum class SupportedLogger { Console, Text };
enum class SupportedReader { Console, Text };

std::optional<SupportedLogger> getSupportedLogerFromString(
    const std::string& loggerStr);
std::optional<SupportedReader> getSupportedReaderFromString(
    const std::string& readerStr);

std::unique_ptr<ILogger> getLoggerFromType(SupportedLogger loggerType);
std::unique_ptr<IReader> getReaderFromType(SupportedReader readerType);

int main(void) {
    SimpleTextReader textInputReader("../paths.txt");
    TextLogger textLogger("../results.txt");
    InputReader inputReader;
    ConsoleLogger logger;

    // read user input
    std::set<TimedPath> pathSet;

    try {
        pathSet = textInputReader.readPathsSet();
    } catch (std::runtime_error err) {
        std::cerr << "Failed to load timed path! " << err.what() << std::endl;
    }

    // perform the analysis
    std::set<TimedPath> validPathSet =
        analysis::removeUnreachablePaths(pathSet);
    std::optional<TimedPath> maximumLatencyPath =
        analysis::getPathWithMaximumLatency(validPathSet);

    // idenrify which paths turned out to be invalid
    std::set<TimedPath> invalidPathSet;
    for (const auto& path : pathSet) {
        if (validPathSet.find(path) == validPathSet.end()) {
            invalidPathSet.insert(path);
        }
    }

    // log results
    try {
        textLogger.logResults(pathSet, validPathSet, invalidPathSet,
                              maximumLatencyPath);
    } catch (std::runtime_error err) {
        std::cerr << "Failed to log results! " << err.what() << std::endl;
    }

    return 0;
}

std::optional<SupportedLogger> getSupportedLogerFromString(
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

std::optional<SupportedReader> getSupportedReaderFromString(
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

std::unique_ptr<ILogger> getLoggerFromType(SupportedLogger loggerType) {
    std::string outputPath;
    switch (loggerType) {
        case SupportedLogger::Console:
            return std::make_unique<ConsoleLogger>();

        case SupportedLogger::Text:
            std::cout << "Enter output path: ";
            std::cin >> outputPath;
            return std::make_unique<TextLogger>(outputPath);

        default:
            return nullptr;
    }

    return nullptr;
}

std::unique_ptr<IReader> getReaderFromType(SupportedReader readerType) {
    std::string inputPath;
    switch (readerType) {
        case SupportedReader::Console:
            return std::make_unique<InputReader>();

        case SupportedReader::Text:
            std::cout << "Enter path to input file: ";
            std::cin >> inputPath;
            return std::make_unique<SimpleTextReader>(inputPath);

        default:
            return nullptr;
    }

    return nullptr;
}