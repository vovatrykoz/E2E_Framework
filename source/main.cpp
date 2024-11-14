#include <Analysis.h>
#include <Setup.h>

#include <iostream>
#include <memory>
#include <optional>

void printUsageInfo();

int main(int argc, char* argv[]) {
    // prepare the reader and the logger
    std::unique_ptr<IReader> inputReader = nullptr;
    std::unique_ptr<ILogger> logger = nullptr;

    // setup
    switch (argc) {
        case 0:
            // default to console if the user has not provided any input
            inputReader =
                setup::getReaderFromType(setup::SupportedReader::Console);
            logger = setup::getLoggerFromType(setup::SupportedLogger::Console);
            break;

        case 1:
            // if only one parameter is provided, we assume that to be a reader
            // deafault to console logger
            inputReader = setup::reader(argv[0]);
            logger = setup::getLoggerFromType(setup::SupportedLogger::Console);
            break;

        case 2:
            inputReader = setup::reader(argv[0]);
            logger = setup::logger(argv[1]);
            break;

        default:
            std::cerr << "Too many parameters" << std::endl;
            break;
    }

    if (logger == nullptr || inputReader == nullptr) {
        std::cerr << "Setup incomplete, please try again" << std::endl;
        printUsageInfo();
        return -1;
    }

    std::set<TimedPath> pathSet;

    // read user input
    try {
        pathSet = inputReader->readPathsSet();
    } catch (std::runtime_error err) {
        std::cerr << "Failed to load timed path! " << err.what() << std::endl;
        return -1;
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
        logger->logResults(pathSet, validPathSet, invalidPathSet,
                           maximumLatencyPath);
    } catch (std::runtime_error err) {
        std::cerr << "Failed to log results! " << err.what() << std::endl;
        return -1;
    }

    return 0;
}

void printUsageInfo() {
    std::cerr << "Usage: runner <reader_type> <logger_type>" << std::endl;
    std::cerr << "Currently supported loggers: Console, Text" << std::endl;
    std::cerr << "Currently supported readers: Console, Text" << std::endl;
}
