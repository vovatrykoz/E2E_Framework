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
        writerTaskInstance.activationTime + writerTaskInstance.wcet;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}
