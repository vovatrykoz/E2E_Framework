#include <Analysis.h>
#include <TaskScheduling.h>
#include <io/logger/ConsoleSystemLogger.h>
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
    std::unique_ptr<ITaskReader> inputReader = nullptr;
    std::unique_ptr<IResultLogger> resultLogger = nullptr;
    std::unique_ptr<ISystemLogger> systemLogger =
        std::make_unique<ConsoleSystemLogger>();

    // setup
    switch (argc) {
        case 1:
            // use presets the user has not provided any input
            inputReader = setup::preset::makeDefaultTaskReader();
            resultLogger = setup::preset::makeDefaultSimplifiedLogger();
            break;

        case 2:
            // if only one parameter is provided, we assume that to be a reader
            // default to presets for the logger
            inputReader = setup::taskReader(argv[1]);
            resultLogger = setup::preset::makeDefaultSimplifiedLogger();
            break;

        case 3:
            inputReader = setup::taskReader(argv[1]);
            resultLogger = setup::simpleLogger(argv[2]);
            break;

        default:
            systemLogger->logError("Too many parameters");
            break;
    }

    if (resultLogger == nullptr || inputReader == nullptr) {
        systemLogger->logError("Setup incomplete, please try again");
        printUsageInfo();
        return -1;
    }

    std::vector<NamedTask> namedTasks;
    // read user input
    try {
        namedTasks = inputReader->readTaskChain();
    } catch (const std::exception& ex) {
        systemLogger->logError("Failed to load tasks! " +
                               std::string(ex.what()));
        return -1;
    } catch (...) {
        systemLogger->logError(
            "Unknown error has occured while reading the task chain! "
            "Please try again!");
        return -1;
    }

    std::vector<OffsetPeriodicTask> taskChain;
    taskChain.reserve(namedTasks.size());
    for (const auto& namedTask : namedTasks) {
        taskChain.push_back(namedTask.task);
    }

    // given a set of tasks, we generate every possible task instance in the
    // set, as well as every possible timed path
    systemLogger->logInfo("Generating task instances");
    std::vector<std::vector<PeriodicTaskInstance>> taskInstances;
    try {
        taskInstances = scheduling::generateTaskInstancesFromPath(taskChain);
    } catch (std::bad_alloc) {
        systemLogger->logError(
            "The provided input resulted in too many task instances "
            "being generated. Review your task parameters to ensure "
            "a reasonable number of task instances can be generated");
        return 0;
    }

    systemLogger->logInfo("Building all possible execution paths");
    std::vector<std::vector<PeriodicTaskInstance>> allPossiblePaths;
    try {
        allPossiblePaths = scheduling::buildTaskExecutionPaths(taskInstances);
    } catch (std::bad_alloc) {
        systemLogger->logError(
            "The provided input resulted in too many task exectution paths "
            "being genereated. Review your task parameters to ensure "
            "a reasonable number of task instances can be generated");
        return 0;
    }

    systemLogger->logInfo("Preparing the timed paths for the analysis");
    const std::multiset<TimedPath> pathSet =
        scheduling::generateTimedPathsFromInstances(allPossiblePaths);

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
    // indentify which paths turned out to be invalid
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

    systemLogger->logInfo("Analysis done!");

    // log results
    try {
        resultLogger->logValidAndInvalidPaths(pathSet, validPathSet_LL,
                                              invalidPathSet);
        resultLogger->logResults_LL(maximumLatencyPath_LL);
        resultLogger->logResults_LF(maximumLatencyPath_LF);
        resultLogger->logResults_FL(maxFirstToLastDelay);
        resultLogger->logResults_FF(maxFirstToFirstDelay);
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

    return 0;
}

void printUsageInfo() {
    std::cout << "Usage: taskAnalyzer <reader_type> <logger_type>" << "\n";
    std::cout << "Currently supported loggers: Console, Text" << "\n";
    std::cout << "Currently supported readers: Console, Text" << "\n";
}
