#include "TimedPath.h"

void TimedPath::popTaskInstance() {
    if (this->tasks.empty()) {
        return;
    }

    this->tasks.pop_back();
}

int TimedPath::endToEndDelay() const {
    if (this->tasks.empty()) {
        return 0;
    }

    int size = this->tasks.size();
    if (size == 1) {
        return this->tasks[0].baseTask.wcet;
    }

    const TaskInstance& lastTaskInstance = this->tasks[size - 1];
    const TaskInstance& firstTaskInstance = this->tasks[0];

    return lastTaskInstance.activationTime + lastTaskInstance.baseTask.wcet -
           firstTaskInstance.activationTime;
}
