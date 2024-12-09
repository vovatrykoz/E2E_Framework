#include "TimedPath.h"

#include <numeric>

using namespace e2e;

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

    std::size_t size = this->tasks.size();
    if (size == 1) {
        return this->tasks[0].baseTask.wcrt;
    }

    const PeriodicTaskInstance& lastTaskInstance = this->tasks[size - 1];
    const PeriodicTaskInstance& firstTaskInstance = this->tasks[0];

    return lastTaskInstance.activationTime + lastTaskInstance.baseTask.wcrt -
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

    std::size_t lastElementIndex = this->tasks.size() - 1;
    return this->tasks[lastElementIndex].activationTime;
}

bool TimedPath::succeeds(const TimedPath& other) const {
    int thisPathPeriod = this->calculatePathPeriod();
    int otherPathPeriod = other.calculatePathPeriod();

    if (thisPathPeriod != otherPathPeriod) {
        return false;
    }

    int otherPathInstanceResetTime =
        other.firstTaskActivationTime() + otherPathPeriod;

    return this->firstTaskActivationTime() == otherPathInstanceResetTime;
}

int TimedPath::calculatePathPeriod() const {
    if (this->tasks.empty()) {
        return 0;
    }

    int acc = 1;
    for (const auto& taskInstance : this->tasks) {
        acc = std::lcm(taskInstance.baseTask.period, acc);
    }

    return acc;
}
