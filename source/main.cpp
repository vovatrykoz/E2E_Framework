#include <Analysis.h>

#include <iostream>
#include <limits>
#include <optional>

int readInt(const std::string& message);
TaskInstance readTaskInstance();

int main(void) {
    Task task(10, 5, 1);
    std::string taskChainName;
    int numOfTasks;

    std::cout << "Enter task chain name: ";
    std::cin >> taskChainName;

    TimedPath timedPath;

    numOfTasks = readInt("How many tasks should be in the chain: ");

    for (int i = 0; i < numOfTasks; i++) {
        std::cout << "Reading Task " << i + 1 << std::endl;
        TaskInstance taskInstance = readTaskInstance();
        timedPath.appendTaskInstance(taskInstance);
        std::cout << std::endl;
    }

    std::cout << "End to end timing: " << timedPath.endToEndDelay() << std::endl;

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
