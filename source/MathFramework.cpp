#include "MathFramework.h"

bool MathFramework::att(const TaskInstance& writerTaskInstance,
                        const TaskInstance& readerTaskInstance) {
    if (readerTaskInstance.activationTime < writerTaskInstance.activationTime) {
        return true;
    }

    return false;
}

bool MathFramework::crit(const TaskInstance& writerTaskInstance,
                         const TaskInstance& readerTaskInstance) {
    int writerTaskTerminationTime =
        writerTaskInstance.activationTime + writerTaskInstance.baseTask.wcet;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}

bool MathFramework::wait(const Task& writerTask, const Task& readerTask) {
    if (readerTask.priority < writerTask.priority) {
        return true;
    }

    return false;
}

bool MathFramework::forw(const TaskInstance& writerTaskInstance,
                         const TaskInstance& readerTaskInstance) {
    bool instancesDoNotTimeTravel =
        !att(writerTaskInstance, readerTaskInstance);
    bool instancesAreNonCritical =
        !crit(writerTaskInstance, readerTaskInstance);
    bool readerHasToWait =
        wait(writerTaskInstance.baseTask, readerTaskInstance.baseTask);

    if (instancesDoNotTimeTravel &&
        (instancesAreNonCritical || readerHasToWait)) {
        return true;
    }

    return false;
}

bool MathFramework::reach(const TaskInstance& currentWriterTaskInstance,
                          const TaskInstance& readerTaskInstance,
                          const TaskInstance& nextWriterTaskInstance) {
    return true;
}
