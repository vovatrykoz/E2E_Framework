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

bool MathFramework::pathReach(const std::vector<TaskInstancePair>& timedPath) {
    if(timedPath.empty()) {
        return false;
    }

    if(timedPath.size() == 1) {
        return true;
    }

    for(int i = 0; i < timedPath.size() - 2; i++) {
        
    }

    return true;
}
