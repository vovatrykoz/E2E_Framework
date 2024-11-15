#include "TimedPath.h"

#include <numeric>

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

int TimedPath::firstTaskActivationTime() const {
    if (this->tasks.empty()) {
        return 0;
    }

    return this->tasks[0].activationTime;
}

int TimedPath::lastTaskActivationTime() const {
    if (this->tasks.empty()) {
        return 0;
    }

    size_t lastElementIndex = this->tasks.size() - 1;
    return this->tasks[lastElementIndex].activationTime;
}

bool TimedPath::succeeds(const TimedPath& other) const {
    int thisPathPeriod = this->calculatePathPeriod();
    int otherPathPeriod = other.calculatePathPeriod();

    if (thisPathPeriod != otherPathPeriod) {
        return false;
    }

    int otherPathEndTime = other.firstTaskActivationTime() + other.endToEndDelay();

    return this->firstTaskActivationTime() == otherPathEndTime;
}

int TimedPath::calculatePathPeriod() const {
    if (this->tasks.empty()) {
        return 0;
    }

    if (this->tasks.size() == 1) {
        return this->tasks[0].baseTask.period;
    }

    int acc = 1;
    for (int i = 0; i < this->tasks.size() - 1; i++) {
        acc = std::lcm(this->tasks[i].baseTask.period, acc);
    }

    return acc;
}
