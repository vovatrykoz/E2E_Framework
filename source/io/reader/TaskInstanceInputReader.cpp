#include <iostream>
#include <limits>

#include "io/reader/ConsoleTaskInstanceReader.h"

using namespace e2e;
using namespace e2e::io;

std::multiset<TimedPath> ConsoleTaskInstanceReader::readPathsSet() const {
    std::multiset<TimedPath> result;
    std::string name;
    const int numOfChains =
        readInt("How many task chains do you want to analyse: ");

    for (int i = 0; i < numOfChains; i++) {
        std::cout << "Enter task chain name: ";
        std::cin >> name;
        std::cout << std::endl;

        TimedPath timedPath = readTimedPath(name);
        result.insert(timedPath);
    }

    return result;
}

int ConsoleTaskInstanceReader::readInt(const std::string& message) const {
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

PeriodicTaskInstance ConsoleTaskInstanceReader::readTaskInstance() const {
    const int period = this->readInt("Enter task period: ");
    const int wcrt =
        this->readInt("Enter worst case response time for the task: ");
    const int priority = this->readInt("Enter task priority: ");
    const int activationTime =
        this->readInt("Enter task activation time or offset: ");

    return PeriodicTaskInstance(PeriodicTask(period, wcrt, priority),
                                activationTime);
}

TimedPath ConsoleTaskInstanceReader::readTimedPath(
    const std::string& name) const {
    TimedPath timedPath(name);

    const int numOfTasks = readInt("How many tasks should be in the chain: ");

    for (int i = 0; i < numOfTasks; i++) {
        std::cout << "Reading Task " << i + 1 << std::endl;
        const PeriodicTaskInstance taskInstance = this->readTaskInstance();
        timedPath.appendTaskInstance(taskInstance);
        std::cout << std::endl;
    }

    return timedPath;
}