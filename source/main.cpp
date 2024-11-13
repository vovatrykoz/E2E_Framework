#include <Task.h>

#include <iostream>

int main(void) {
    Task task(10, 5);

    std::cout << "Created a task with period " << task.period << " and wcet "
              << task.wcet << std::endl;

    return 0;
}