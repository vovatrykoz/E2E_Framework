#include <Analysis.h>
#include <setup/Preset.h>
#include <setup/Setup.h>

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
            inputReader = setup::preset::makeDefaultTaskInstanceReader();
            logger = setup::preset::makeDefaultLogger();
            break;

        case 2:
            // if only one parameter is provided, we assume that to be a reader
            // deafault to preset for the logger
            inputReader = setup::taskInstanceReader(argv[1]);
            logger = setup::preset::makeDefaultLogger();
            break;

        case 3:
            inputReader = setup::taskInstanceReader(argv[1]);
            logger = setup::logger(argv[2]);
            break;

        default:
            std::cerr << "Too many parameters" << "\n";
            break;
    }

    if (logger == nullptr || inputReader == nullptr) {
        std::cerr << "Setup incomplete, please try again" << "\n";
        printUsageInfo();
        return -1;
    }

    std::multiset<TimedPath> pathSet;

    // read user input
    try {
        pathSet = inputReader->readPathsSet();
    } catch (const std::exception& ex) {
        std::cerr << "Failed to load timed paths! " << ex.what() << "\n";
        return 0;
    } catch (...) {
        std::cerr << "Unknown error has occured while reading the path set! "
                     "Please try again! "
                  << "\n";
        return 0;
    }

    // perform the analysis
    const std::multiset<TimedPath> validPathSet_LL =
        analysis::removeUnreachablePaths(pathSet);

    // perform end-to-end analysis using Last-to-Last semantics
    const std::optional<TimedPath> maximumLatencyPath_LL =
        analysis::getPathWithMaximumLatency(validPathSet_LL);

    // get a set for Last-To-First semantics analysis
    const std::multiset<TimedPath> validPathSet_LF =
        analysis::removePathsProducingDuplicateValues(validPathSet_LL);

    // perform end-to-end analysis using Last-To-First semantics
    const std::optional<TimedPath> maximumLatencyPath_LF =
        analysis::getPathWithMaximumLatency(validPathSet_LF);

    // perform end-to-end analysis using First-To-Last semantics
    const int maxFirstToLastDelay =
        analysis::getOverarchingDelay(validPathSet_LL);

    // perform end-to-end analysis using First-To-First semantics
    const int maxFirstToFirstDelay =
        analysis::getOverarchingDelay(validPathSet_LF);

    // idenrify which paths turned out to be invalid
    const std::multiset<TimedPath> invalidPathSet = [&validPathSet_LL,
                                                     &pathSet]() {
        std::multiset<TimedPath> invalidPathSet;

        for (const auto& path : pathSet) {
            if (validPathSet_LL.find(path) == validPathSet_LL.end()) {
                invalidPathSet.insert(path);
            }
        }

        return invalidPathSet;
    }();

    // log results
    try {
        logger->logValidAndInvalidPaths(pathSet, validPathSet_LL,
                                        invalidPathSet);
        logger->logResults_LL(maximumLatencyPath_LL);
        logger->logResults_LF(maximumLatencyPath_LF);
        logger->logResults_FL(maxFirstToLastDelay);
        logger->logResults_FF(maxFirstToFirstDelay);
    } catch (const std::exception& ex) {
        std::cerr << "Failed to log results! " << ex.what() << "\n";
        return 0;
    } catch (...) {
        std::cerr << "Unknown error has occured while logging the results! "
                     "Please try again! "
                  << "\n";
        return 0;
    }

    return 0;
}

void printUsageInfo() {
    std::cerr << "Usage: individualPathAnalyzer <reader_type> <logger_type>"
              << "\n";
    std::cerr << "Currently supported loggers: Console, Text" << "\n";
    std::cerr << "Currently supported readers: Console, Text" << "\n";
}
