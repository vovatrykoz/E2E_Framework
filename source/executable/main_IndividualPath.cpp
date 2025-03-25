#include <Analysis.h>
#include <io/logger/ConsoleSystemLogger.h>
#include <setup/Preset.h>
#include <setup/Setup.h>

#include <iostream>
#include <memory>
#include <optional>

using namespace e2e;
using namespace e2e::io;

void logUsageInfo(ISystemLogger* systemLogger);

int main(int argc, char* argv[]) {
    // prepare the reader and the logger
    std::unique_ptr<ITaskInstanceReader> inputReader = nullptr;
    std::unique_ptr<IResultLogger> logger = nullptr;

    const std::function<void(console::Color)>& consoleColorFunc =
        console::setColorTo;
    std::unique_ptr<ISystemLogger> systemLogger =
        std::make_unique<ConsoleSystemLogger>(consoleColorFunc);

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
            systemLogger->logError("Too many parameters");
            break;
    }

    if (logger == nullptr || inputReader == nullptr) {
        systemLogger->logError("Setup incomplete, please try again");
        logUsageInfo(systemLogger.get());
        return -1;
    }

    std::multiset<TimedPath> pathSet;

    // read user input
    try {
        pathSet = inputReader->readPathsSet();
    } catch (const std::exception& ex) {
        systemLogger->logError("Failed to load timed path! " +
                               std::string(ex.what()));
        return -1;
    } catch (...) {
        systemLogger->logError(
            "Unknown error has occured while reading the path set! "
            "Please try again!");
        return -1;
    }

    systemLogger->logInfo("Performing end-to-end analysis with LL semantics");
    // perform the analysis
    const std::multiset<TimedPath> validPathSet_LL =
        analysis::removeUnreachablePaths(pathSet);

    // perform end-to-end analysis using Last-to-Last semantics
    const std::optional<TimedPath> maximumLatencyPath_LL =
        analysis::getPathWithMaximumLatency(validPathSet_LL);

    systemLogger->logInfo("Performing end-to-end analysis with LF semantics");
    // get a set for Last-To-First semantics analysis
    const std::multiset<TimedPath> validPathSet_LF =
        analysis::removePathsProducingDuplicateValues(validPathSet_LL);

    // perform end-to-end analysis using Last-To-First semantics
    const std::optional<TimedPath> maximumLatencyPath_LF =
        analysis::getPathWithMaximumLatency(validPathSet_LF);

    systemLogger->logInfo("Performing end-to-end analysis with FL semantics");
    // perform end-to-end analysis using First-To-Last semantics
    const int maxFirstToLastDelay =
        analysis::getOverarchingDelay(validPathSet_LL);

    systemLogger->logInfo("Performing end-to-end analysis with FF semantics");
    // perform end-to-end analysis using First-To-First semantics
    const int maxFirstToFirstDelay =
        analysis::getOverarchingDelay(validPathSet_LF);

    systemLogger->logInfo("Identifying invalid paths");
    // identify which paths turned out to be invalid
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
        systemLogger->logError("Failed to log results! " +
                               std::string(ex.what()));
        return 0;
    } catch (...) {
        systemLogger->logError(
            "Unknown error has occured while logging the results! "
            "Please try again!");
        return 0;
    }

    systemLogger->logInfo("Exiting the application");

    return 0;
}

void logUsageInfo(ISystemLogger* systemLogger) {
    systemLogger->logMessage(
        "Usage: taskAnalyzer <reader_type> <logger_type>\n");
    systemLogger->logMessage("Currently supported loggers: Console, Text\n");
    systemLogger->logMessage("Currently supported readers: Console, Text\n");
}
