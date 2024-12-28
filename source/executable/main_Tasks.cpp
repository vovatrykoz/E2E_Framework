#include <Analysis.h>
#include <TaskScheduling.h>
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
    std::unique_ptr<ILogger> logger = nullptr;

    // setup
    switch (argc) {
        case 1:
            // use presets the user has not provided any input
            inputReader = setup::preset::makeDefaultTaskReader();
            logger = setup::preset::makeDefaultSimplifiedLogger();
            break;

        case 2:
            // if only one parameter is provided, we assume that to be a reader
            // deafault to presets for the logger
            inputReader = setup::taskReader(argv[1]);
            logger = setup::preset::makeDefaultSimplifiedLogger();
            break;

        case 3:
            inputReader = setup::taskReader(argv[1]);
            logger = setup::simpleLogger(argv[2]);
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

    std::vector<NamedTask> namedTasks;

    // read user input
    try {
        namedTasks = inputReader->readTaskChain();
    } catch (std::runtime_error err) {
        std::cerr << "Failed to load tasks! " << err.what() << std::endl;
        return -1;
    }

    std::vector<PeriodicTask> taskChain;
    taskChain.reserve(namedTasks.size());
    for (const auto& namedTask : namedTasks) {
        taskChain.push_back(namedTask.task);
    }

    // given a set of tasks, we generate every possible task instance in the
    // set, as well as every possible timed path
    std::vector<std::vector<PeriodicTaskInstance>> taskInstances;
    try {
        taskInstances = scheduling::generateTaskInstancesFromPath(taskChain);
    } catch (std::bad_alloc) {
        std::cout << "The provided input resulted in too many task instances "
                     "being genereated. Review your task parameters to ensure "
                     "a reasonable number of taks instances can be generated"
                  << std::endl;
        return 0;
    }

    std::vector<std::vector<PeriodicTaskInstance>> allPossiblePaths;
    try {
        allPossiblePaths = scheduling::buildTaskExecutionPaths(taskInstances);
    } catch (std::bad_alloc) {
        std::cout
            << "The provided input resulted in too many task exectution paths "
               "being genereated. Review your task parameters to ensure "
               "a reasonable number of taks instances can be generated"
            << std::endl;
        return 0;
    }

    const std::multiset<TimedPath> pathSet =
        scheduling::generateTimedPathsFromInstances(allPossiblePaths);

    // perform the analysis
    const std::multiset<TimedPath> validPathSet_LL =
        analysis::removeUnreachablePaths(pathSet);

    // perform end-to-end analysis using Last-to-Last semantics
    const std::optional<TimedPath> maximumLatencyPath_LL =
        analysis::getPathWithMaximumLatency(validPathSet_LL);

    // get a set for Last-To-First semantics analysis
    const std::multiset<TimedPath> validPathSet_LF =
        analysis::removePathsProducingDublicateValues(validPathSet_LL);

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
    std::cerr << "Usage: taskAnalyzer <reader_type> <logger_type>" << std::endl;
    std::cerr << "Currently supported loggers: Console, Text" << std::endl;
    std::cerr << "Currently supported readers: Console, Text" << std::endl;
}
