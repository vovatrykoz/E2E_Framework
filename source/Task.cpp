#include "Task.h"

TaskInstance TaskInstance::nextInstance() const {
    int nextActivationTime = this->activationTime + this->baseTask.period;
    return TaskInstance(this->baseTask, nextActivationTime);
}