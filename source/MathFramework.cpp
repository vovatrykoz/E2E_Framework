#include "MathFramework.h"

using namespace e2e;

bool mathframework::att(const TaskInstance& writerTaskInstance,
                        const TaskInstance& readerTaskInstance) {
    if (readerTaskInstance.activationTime < writerTaskInstance.activationTime) {
        return true;
    }

    return false;
}

bool mathframework::crit(const TaskInstance& writerTaskInstance,
                         const TaskInstance& readerTaskInstance) {
    int writerTaskTerminationTime =
        writerTaskInstance.activationTime + writerTaskInstance.baseTask.wcrt;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}

bool mathframework::wait(const Task& writerTask, const Task& readerTask) {
    if (readerTask.priority < writerTask.priority) {
        return true;
    }

    return false;
}

bool mathframework::forw(const TaskInstance& writerTaskInstance,
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

bool mathframework::reach(const TaskInstance& currentWriterTaskInstance,
                          const TaskInstance& readerTaskInstance,
                          const TaskInstance& nextWriterTaskInstance) {
    bool readerInstanceIsReachable =
        forw(currentWriterTaskInstance, readerTaskInstance);
    bool nextWriterInstanceCannotReachReaderInstance =
        !forw(nextWriterTaskInstance, readerTaskInstance);

    if (readerInstanceIsReachable &&
        nextWriterInstanceCannotReachReaderInstance) {
        return true;
    }

    return false;
}

bool mathframework::pathReach(const std::vector<TaskInstance>& timedPath) {
    if (timedPath.empty()) {
        return false;
    }

    std::size_t pathSize = timedPath.size();
    if (pathSize == 1) {
        return true;
    }

    for (std::size_t i = 0; i < pathSize - 1; i++) {
        if (!reach(timedPath[i],
                   timedPath[i + 1],
                   timedPath[i].nextInstance())) {
            return false;
        }
    }

    return true;
}
