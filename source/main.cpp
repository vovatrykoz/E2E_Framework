#include <Analysis.h>
#include <ConsoleLogger.h>

#include <iostream>
#include <limits>
#include <optional>

int readInt(const std::string& message);
TaskInstance readTaskInstance();
TimedPath readTimedPath(const std::string& name);
std::set<TimedPath> readPathsSet();

int main(void) {
    ConsoleLogger logger;

    std::set<TimedPath> pathSet = readPathsSet();
    std::set<TimedPath> validPathSet = analysis::removeUnreachablePaths(pathSet);
    int maximumLatency = analysis::calculateMaximumLatency(validPathSet);

    std::set<TimedPath> invalidPathSet;
    for(const auto& path : pathSet) {
        if(validPathSet.find(path) == validPathSet.end()) {
            invalidPathSet.insert(path);
        }
    }

    logger.logResults(pathSet, validPathSet, invalidPathSet, maximumLatency);

    return 0;
}

int readInt(const std::string& message) {
    int output;
    bool validInput = false;

    do {
        std::cout << message;
        std::cin >> output;

        if (std::cin.fail()) {
            std::cout << std::endl
                      << "The input was not an integer, please try again"
                      << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    } while (!validInput);

    return output;
}

TaskInstance readTaskInstance() {
    int period = readInt("Enter task period: ");
    int wcet = readInt("Enter worst case execution time for the task: ");
    int priority = readInt("Enter task priority: ");
    int activationTime = readInt("Enter task activation time or offset: ");

    return TaskInstance(Task(period, wcet, priority), activationTime);
}

TimedPath readTimedPath(const std::string& name) {
    TimedPath timedPath(name);

    int numOfTasks = readInt("How many tasks should be in the chain: ");

    for (int i = 0; i < numOfTasks; i++) {
        std::cout << "Reading Task " << i + 1 << std::endl;
        TaskInstance taskInstance = readTaskInstance();
        timedPath.appendTaskInstance(taskInstance);
        std::cout << std::endl;
    }

    return timedPath;
}

std::set<TimedPath> readPathsSet() {
    std::set<TimedPath> result;
    std::string name;
    int numOfChains = readInt("How many task chains do you want to analyse: ");

    for (int i = 0; i < numOfChains; i++) {
        std::cout << "Enter task chain name: ";
        std::cin >> name;
        std::cout << std::endl;

        TimedPath timedPath = readTimedPath(name);
        result.insert(timedPath);
    }

    return result;
}