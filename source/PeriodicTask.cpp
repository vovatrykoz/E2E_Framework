#include <e2e/PeriodicTask.h>

using namespace e2e;

// Calculate the next instance's activation time based on the current activation
// time and the task's period.
PeriodicTaskInstance PeriodicTaskInstance::nextInstance() const {
    const int nextActivationTime = this->activationTime + this->baseTask.period;
    return PeriodicTaskInstance(this->baseTask, nextActivationTime);
}
