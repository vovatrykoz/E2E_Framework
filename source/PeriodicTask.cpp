#include "PeriodicTask.h"

using namespace e2e;

PeriodicTaskInstance PeriodicTaskInstance::nextInstance() const {
    int nextActivationTime = this->activationTime + this->baseTask.period;
    return PeriodicTaskInstance(this->baseTask, nextActivationTime);
}