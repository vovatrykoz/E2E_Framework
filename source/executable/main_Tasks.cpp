#include <Analysis.h>
#include <TaskScheduling.h>
#include <Setup.h>

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
            // default to console if the user has not provided any input
            inputReader =
                setup::getTaskReaderFromType(setup::SupportedTaskReader::Console);
            logger = setup::getLoggerFromType(setup::SupportedLogger::SimplifiedConsole);
            break;

        case 2:
            // if only one parameter is provided, we assume that to be a reader
            // deafault to console logger
            inputReader = setup::taskReader(argv[1]);
            logger = setup::getLoggerFromType(setup::SupportedLogger::SimplifiedConsole);
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

    std::vector<Task> taskChain;
    taskChain.reserve(namedTasks.size());
    for(const auto& namedTask : namedTasks) {
        taskChain.push_back(namedTask.task);
    }

    std::vector<std::vector<TaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromTasks(taskChain);

    std::vector<std::vector<TaskInstance>> allPossiblePaths =
        scheduling::buildTimedPaths(taskInstances);

    std::set<TimedPath> pathSet =
        scheduling::generateTimedPaths(allPossiblePaths);

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
    std::cerr << "Usage: taskAnalyzer <reader_type> <logger_type>" << std::endl;
    std::cerr << "Currently supported loggers: Console, Text" << std::endl;
    std::cerr << "Currently supported readers: Console, Text" << std::endl;
}
