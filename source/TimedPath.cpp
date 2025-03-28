#include <e2e/TimedPath.h>

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

    if (this->tasks.size() == 1) {
        return this->tasks.front().baseTask.wcrt;
    }

    const PeriodicTaskInstance lastTaskInstance = this->tasks.back();
    const PeriodicTaskInstance firstTaskInstance = this->tasks.front();

    return lastTaskInstance.activationTime + lastTaskInstance.baseTask.wcrt -
           firstTaskInstance.activationTime;
}

int TimedPath::firstTaskActivationTime() const {
    if (this->tasks.empty()) {
        return 0;
    }

    return this->tasks.front().activationTime;
}

int TimedPath::lastTaskActivationTime() const {
    if (this->tasks.empty()) {
        return 0;
    }

    return this->tasks.back().activationTime;
}

bool TimedPath::succeeds(const TimedPath& other) const {
    const int thisPathPeriod = this->calculatePathPeriod();
    const int otherPathPeriod = other.calculatePathPeriod();

    if (thisPathPeriod != otherPathPeriod) {
        return false;
    }

    const int otherPathInstanceResetTime =
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
