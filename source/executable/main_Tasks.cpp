#include <Analysis.h>
#include <TaskScheduling.h>
#include <io/logger/ConsoleColor.h>
#include <io/logger/ConsoleSystemLogger.h>
#include <setup/Preset.h>
#include <setup/Setup.h>

#include <iostream>
#include <memory>
#include <optional>

using namespace e2e;
using namespace e2e::io;

enum class ArgsProcessingStep { Unspecified, ReadingReader, ReadingLogger };

static const std::string readerOptionShort = "-r";
static const std::string readerOptionLong = "-reader";
static const std::string loggerOptionShort = "-l";
static const std::string loggerOptionLong = "-logger";

void logUsageInfo(const ISystemLogger* systemLogger);

int main(int argc, char* argv[]) {
    const std::function<void(console::Color)>&
        functionForSettingConsoleTextColor = console::setColorTo;

    const std::unique_ptr<ISystemLogger> systemLogger =
        std::make_unique<ConsoleSystemLogger>(
            functionForSettingConsoleTextColor);

    // prepare the reader and the logger
    std::unique_ptr<ITaskReader> inputReader = nullptr;
    std::unique_ptr<IResultLogger> resultLogger = nullptr;

    std::string filePath;

    ArgsProcessingStep currentStep = ArgsProcessingStep::Unspecified;

    if (argc <= 1) {
        systemLogger->logError(
            "Too few arguments! The path to the file to be analyzed is "
            "required");
        logUsageInfo(systemLogger.get());
        return -1;
    } else {
        for (int i = 1; i < argc; i++) {
            if (currentStep == ArgsProcessingStep::ReadingReader) {
                inputReader =
                    setup::taskReader(argv[i], filePath, systemLogger.get());
                currentStep = ArgsProcessingStep::Unspecified;
                continue;
            }

            if (currentStep == ArgsProcessingStep::ReadingLogger) {
                resultLogger = setup::simpleLogger(argv[i]);
                currentStep = ArgsProcessingStep::Unspecified;
                continue;
            }

            if (argv[i] == readerOptionShort || argv[i] == readerOptionLong) {
                currentStep = ArgsProcessingStep::ReadingReader;
            } else if (argv[i] == loggerOptionShort ||
                       argv[i] == loggerOptionLong) {
                currentStep = ArgsProcessingStep::ReadingLogger;
            } else {
                filePath = argv[i];
            }
        }
    }

    if (currentStep == ArgsProcessingStep::ReadingReader) {
        systemLogger->logError(
            "The reader type has to be provided if the -r|-reader "
            "option is used");
        logUsageInfo(systemLogger.get());
        return -1;
    }

    if (currentStep == ArgsProcessingStep::ReadingLogger) {
        systemLogger->logError(
            "The logger type has to be provided if the -l|-logger "
            "option is used");
        logUsageInfo(systemLogger.get());
        return -1;
    }

    if (inputReader == nullptr) {
        systemLogger->logInfo("Using default reader type: text-based");
        inputReader = setup::preset::makeDefaultTaskReader(filePath);
    }

    if (resultLogger == nullptr) {
        systemLogger->logInfo("Using default result logger type: console");
        resultLogger = setup::preset::makeDefaultSimplifiedLogger();
    }

    if (resultLogger == nullptr || inputReader == nullptr) {
        systemLogger->logError("Setup incomplete, please try again");
        logUsageInfo(systemLogger.get());
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

    systemLogger->logInfo("Exiting the application");

    return 0;
}

void logUsageInfo(const ISystemLogger* systemLogger) {
    systemLogger->logMessage(
        "Usage: taskAnalyzer <reader_type> <logger_type>\n");
    systemLogger->logMessage("Currently supported loggers: Console, Text\n");
    systemLogger->logMessage("Currently supported readers: Console, Text\n");
}
