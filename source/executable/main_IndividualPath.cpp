#include <Analysis.h>
#include <Setup.h>

#include <iostream>
#include <memory>
#include <optional>

using namespace e2e;
using namespace e2e::io;

void printUsageInfo();

int main(int argc, char* argv[]) {
    // prepare the reader and the logger
    std::unique_ptr<ITaskInstanceReader> inputReader = nullptr;
    std::unique_ptr<ILogger> logger = nullptr;

    // setup
    switch (argc) {
        case 1:
            // default to console if the user has not provided any input
            inputReader = setup::getTaskInstanceReaderFromType(
                setup::SupportedTaskInstanceReader::Console);
            logger = setup::getLoggerFromType(setup::SupportedLogger::Console);
            break;

        case 2:
            // if only one parameter is provided, we assume that to be a reader
            // deafault to console logger
            inputReader = setup::taskInstanceReader(argv[1]);
            logger = setup::getLoggerFromType(setup::SupportedLogger::Console);
            break;

        case 3:
            inputReader = setup::taskInstanceReader(argv[1]);
            logger = setup::logger(argv[2]);
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
    std::set<TimedPath> validPathSet_LL =
        analysis::removeUnreachablePaths(pathSet);

    // perform end-to-end analysis using Last-to-Last semantics
    std::optional<TimedPath> maximumLatencyPath_LL =
        analysis::getPathWithMaximumLatency(validPathSet_LL);

    // get a set for Last-To-First semantics analysis
    std::set<TimedPath> validPathSet_LF =
        analysis::removePathsProducingDublicateValues(validPathSet_LL);

    // perform end-to-end analysis using Last-To-First semantics
    std::optional<TimedPath> maximumLatencyPath_LF =
        analysis::getPathWithMaximumLatency(validPathSet_LF);

    // perform end-to-end analysis using First-To-Last semantics
    int maxFirstToLastDelay = analysis::getOverarchingDelay(validPathSet_LL);

    // perform end-to-end analysis using First-To-First semantics
    int maxFirstToFirstDelay = analysis::getOverarchingDelay(validPathSet_LF);

    // idenrify which paths turned out to be invalid
    std::set<TimedPath> invalidPathSet;
    for (const auto& path : pathSet) {
        if (validPathSet_LL.find(path) == validPathSet_LL.end()) {
            invalidPathSet.insert(path);
        }
    }

    // log results
    try {
        logger->logValidInvalidPaths(pathSet, validPathSet_LL, invalidPathSet);
        logger->logResults_LL(maximumLatencyPath_LL);
        logger->logResults_LF(maximumLatencyPath_LF);
        logger->logResults_FL(maxFirstToLastDelay);
        logger->logResults_FF(maxFirstToFirstDelay);
    } catch (std::runtime_error err) {
        std::cerr << "Failed to log results! " << err.what() << std::endl;
        return -1;
    }

    return 0;
}

void printUsageInfo() {
    std::cerr << "Usage: individualPathAnalyzer <reader_type> <logger_type>"
              << std::endl;
    std::cerr << "Currently supported loggers: Console, Text" << std::endl;
    std::cerr << "Currently supported readers: Console, Text" << std::endl;
}
