#include "io/InputReader.h"
#include <limits>

std::set<TimedPath> InputReader::readPathsSet() const {
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

int InputReader::readInt(const std::string& message) const {
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

TaskInstance InputReader::readTaskInstance() const {
    int period = readInt("Enter task period: ");
    int wcet = readInt("Enter worst case execution time for the task: ");
    int priority = readInt("Enter task priority: ");
    int activationTime = readInt("Enter task activation time or offset: ");

    return TaskInstance(Task(period, wcet, priority), activationTime);
}

TimedPath InputReader::readTimedPath(const std::string& name) const {
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