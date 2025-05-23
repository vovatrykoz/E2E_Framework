#include <e2e/Analysis.h>
#include <e2e/TaskScheduling.h>
#include <e2e/io/logger/ConsoleColor.h>
#include <e2e/io/logger/ConsoleSystemLogger.h>
#include <e2e/setup/Preset.h>
#include <e2e/setup/Setup.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>

using namespace e2e;
using namespace e2e::io;

using ReaderSetupFunction = std::function<std::unique_ptr<ITaskReader>()>;
using LoggerSetupFunction = std::function<std::unique_ptr<IResultLogger>()>;

void logUsageInfo(const ISystemLogger* systemLogger);
int processCliArgs(const ISystemLogger* systemLogger, int argc, char* argv[],
                   ReaderSetupFunction& taskReaderSetupCallback,
                   LoggerSetupFunction& resultLoggerSetupCallback,
                   std::string& filePath);

int main(int argc, char* argv[]) {
    const std::function<void(console::Color)>&
        functionForSettingConsoleTextColor = console::setColorTo;

    const std::unique_ptr<ISystemLogger> systemLogger =
        std::make_unique<ConsoleSystemLogger>(
            functionForSettingConsoleTextColor);

    std::string filePath = "";

    ReaderSetupFunction taskReaderSetupCallback = [&filePath, &systemLogger]() {
        systemLogger->logInfo("Using default reader type: text-based");
        return setup::preset::makeDefaultTaskReader(filePath);
    };

    LoggerSetupFunction resultLoggerSetupCallback = [&systemLogger]() {
        systemLogger->logInfo("Using default result logger type: console");
        return setup::preset::makeDefaultSimplifiedLogger();
    };

    const int cliArgsProcessingResult =
        processCliArgs(systemLogger.get(), argc, argv, taskReaderSetupCallback,
                       resultLoggerSetupCallback, filePath);

    if (cliArgsProcessingResult != 0) {
        return -1;
    }

    const std::unique_ptr<ITaskReader> inputReader = taskReaderSetupCallback();
    const std::unique_ptr<IResultLogger> resultLogger =
        resultLoggerSetupCallback();

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
    } catch (const std::bad_alloc&) {
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
    } catch (const std::bad_alloc&) {
        systemLogger->logError(
            "The provided input resulted in too many task exectution paths "
            "being genereated. Review your task parameters to ensure "
            "a reasonable number of task instances can be generated");
        return 0;
    }

    systemLogger->logInfo("Preparing the timed paths for the analysis");
    const std::vector<TimedPath> pathSet =
        scheduling::generateTimedPathsFromInstances(allPossiblePaths);

    systemLogger->logInfo("Performing end-to-end analysis with LL semantics");
    // perform the analysis
    const std::vector<TimedPath> validPathSet_LL =
        analysis::removeUnreachablePaths(pathSet);

    // perform end-to-end analysis using Last-to-Last semantics
    const std::optional<TimedPath> maximumLatencyPath_LL =
        analysis::getPathWithMaximumLatency(validPathSet_LL);

    systemLogger->logInfo("Performing end-to-end analysis with LF semantics");
    // get a set for Last-To-First semantics analysis
    const std::vector<TimedPath> validPathSet_LF =
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
    const std::vector<TimedPath> invalidPathSet = [&validPathSet_LL,
                                                   &pathSet]() {
        std::vector<TimedPath> invalidPathSet;

        for (const auto& path : pathSet) {
            if (std::find(validPathSet_LL.begin(), validPathSet_LL.end(),
                          path) == validPathSet_LL.end()) {
                invalidPathSet.push_back(path);
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
        "Usage: taskAnalyzer <file_path> [-r|-reader <reader_type>] "
        "[-l|-logger <logger_type>]\n");
    systemLogger->logMessage("Currently supported loggers: Console, Text\n");
    systemLogger->logMessage("Currently supported readers: Console, Text\n");
}

enum class ArgsProcessingStep { Unspecified, ReadingReader, ReadingLogger };

static const std::string readerOptionShort = "-r";
static const std::string readerOptionLong = "-reader";
static const std::string loggerOptionShort = "-l";
static const std::string loggerOptionLong = "-logger";

int processCliArgs(const ISystemLogger* systemLogger, int argc, char* argv[],
                   ReaderSetupFunction& taskReaderSetupCallback,
                   LoggerSetupFunction& resultLoggerSetupCallback,
                   std::string& filePath) {
    ArgsProcessingStep currentStep = ArgsProcessingStep::Unspecified;

    if (argc <= 1) {
        systemLogger->logError(
            "Too few arguments! The path to the file to be analyzed is "
            "required");
        logUsageInfo(systemLogger);
        return -1;
    } else {
        for (int i = 1; i < argc; i++) {
            if (currentStep == ArgsProcessingStep::ReadingReader) {
                taskReaderSetupCallback = [readerName = std::string(argv[i]),
                                           filePath, systemLogger]() {
                    return setup::taskReader(readerName, filePath,
                                             systemLogger);
                };

                currentStep = ArgsProcessingStep::Unspecified;
                continue;
            }

            if (currentStep == ArgsProcessingStep::ReadingLogger) {
                resultLoggerSetupCallback = [loggerName = std::string(argv[i]),
                                             systemLogger]() {
                    return setup::simpleLogger(loggerName, systemLogger);
                };

                currentStep = ArgsProcessingStep::Unspecified;
                continue;
            }

            if (argv[i] == readerOptionShort || argv[i] == readerOptionLong) {
                currentStep = ArgsProcessingStep::ReadingReader;
            } else if (argv[i] == loggerOptionShort ||
                       argv[i] == loggerOptionLong) {
                currentStep = ArgsProcessingStep::ReadingLogger;
            } else {
                if (filePath != "") {
                    const std::string unexpectedFilePath = argv[i];

                    systemLogger->logWarning(
                        "Received multiple paths for analysis! The program "
                        "only supports analysing one file at a time. "
                        "Discarding file at \"" +
                        unexpectedFilePath + "\" and keeping \"" + filePath +
                        "\" as the file to analyze");

                    continue;
                }

                filePath = std::string(argv[i]);
            }
        }
    }

    if (currentStep == ArgsProcessingStep::ReadingReader) {
        systemLogger->logError(
            "The reader type has to be provided if the -r|-reader "
            "option is used");
        logUsageInfo(systemLogger);
        return -1;
    }

    if (currentStep == ArgsProcessingStep::ReadingLogger) {
        systemLogger->logError(
            "The logger type has to be provided if the -l|-logger "
            "option is used");
        logUsageInfo(systemLogger);
        return -1;
    }

    return 0;
}
