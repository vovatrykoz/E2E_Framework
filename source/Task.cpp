#include "Task.h"

using namespace e2e;

TaskInstance TaskInstance::nextInstance() const {
    int nextActivationTime = this->activationTime + this->baseTask.period;
    return TaskInstance(this->baseTask, nextActivationTime);
}