#include "MathFramework.h"

using namespace e2e;

bool mathframework::att(const PeriodicTaskInstance& writerTaskInstance,
                        const PeriodicTaskInstance& readerTaskInstance) {
    if (readerTaskInstance.activationTime < writerTaskInstance.activationTime) {
        return true;
    }

    return false;
}

bool mathframework::crit(const PeriodicTaskInstance& writerTaskInstance,
                         const PeriodicTaskInstance& readerTaskInstance) {
    int writerTaskTerminationTime =
        writerTaskInstance.activationTime + writerTaskInstance.baseTask.wcrt;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}

bool mathframework::wait(const PeriodicTask& writerTask,
                         const PeriodicTask& readerTask) {
    if (readerTask.priority < writerTask.priority) {
        return true;
    }

    return false;
}

bool mathframework::forw(const PeriodicTaskInstance& writerTaskInstance,
                         const PeriodicTaskInstance& readerTaskInstance) {
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

bool mathframework::reach(const PeriodicTaskInstance& currentWriterTaskInstance,
                          const PeriodicTaskInstance& readerTaskInstance,
                          const PeriodicTaskInstance& nextWriterTaskInstance) {
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

bool mathframework::pathReach(
    const std::vector<PeriodicTaskInstance>& timedPath) {
    if (timedPath.empty()) {
        return false;
    }

    std::size_t pathSize = timedPath.size();
    if (pathSize == 1) {
        return true;
    }

    for (std::size_t i = 0; i < pathSize - 1; i++) {
        if (!reach(timedPath[i], timedPath[i + 1],
                   timedPath[i].nextInstance())) {
            return false;
        }
    }

    return true;
}
