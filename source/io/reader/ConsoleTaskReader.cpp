#include <e2e/io/reader/ConsoleTaskReader.h>

#include <iostream>
#include <limits>

using namespace e2e::io;

std::vector<NamedTask> ConsoleTaskReader::readTaskChain() const {
    std::vector<NamedTask> result;
    std::string name;
    const int numOfChains = readInt("How many tasks should be in the system: ");

    for (int i = 0; i < numOfChains; i++) {
        const NamedTask task = this->readTask();
        result.push_back(task);

        std::cout << std::endl;
    }

    return result;
}

int ConsoleTaskReader::readInt(const std::string& message) const {
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

NamedTask ConsoleTaskReader::readTask() const {
    std::string name;

    std::cout << "Enter task name: ";
    std::cin >> name;

    const int period = readInt("Enter task period: ");
    const int wcrt = readInt("Enter worst case response time for the task: ");
    const int priority = readInt("Enter task priority: ");
    const int offset = readInt("Enter task offset: ");

    return NamedTask(OffsetPeriodicTask(period, wcrt, priority, offset), name);
}
