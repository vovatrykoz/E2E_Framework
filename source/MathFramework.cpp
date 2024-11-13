#include "MathFramework.h"

bool att(const TaskInstance& writerTaskInstance,
         const TaskInstance& readerTaskInstance) {
    if (readerTaskInstance.activationTime < writerTaskInstance.activationTime) {
        return true;
    }

    return false;
}

bool crit(const TaskInstance& writerTaskInstance,
          const TaskInstance& readerTaskInstance) {
    int writerTaskTerminationTime =
        writerTaskInstance.activationTime + writerTaskInstance.baseTask.wcet;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}

bool wait(const Task& writerTask, const Task& readerTask) { return false; }
