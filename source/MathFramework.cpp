#include "MathFramework.h"

using namespace e2e;

// Return true if the reader task is activated before the writer task
// (activation time travel occurs).
bool mathframework::att(PeriodicTaskInstance writerTaskInstance,
                        PeriodicTaskInstance readerTaskInstance) {
    if (readerTaskInstance.activationTime < writerTaskInstance.activationTime) {
        return true;
    }

    return false;
}
// Check if the reader task overlaps with the writer task, considering the
// writer's worst-case response time (wcrt).
bool mathframework::crit(PeriodicTaskInstance writerTaskInstance,
                         PeriodicTaskInstance readerTaskInstance) {
    const int writerTaskTerminationTime =
        writerTaskInstance.activationTime + writerTaskInstance.baseTask.wcrt;

    if (readerTaskInstance.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}

// Return true if the reader task must wait for the writer task to finish due to
// the writer's higher priority.
bool mathframework::wait(PeriodicTask writerTask, PeriodicTask readerTask) {
    if (readerTask.priority < writerTask.priority) {
        return true;
    }

    return false;
}

// Determine if the reader task can reach the writer task, based on activation
// time travel, criticality, and priority.
bool mathframework::forw(PeriodicTaskInstance writerTaskInstance,
                         PeriodicTaskInstance readerTaskInstance) {
    const bool instancesDoNotTimeTravel =
        !att(writerTaskInstance, readerTaskInstance);
    const bool instancesAreNonCritical =
        !crit(writerTaskInstance, readerTaskInstance);
    const bool readerHasToWait =
        wait(writerTaskInstance.baseTask, readerTaskInstance.baseTask);

    if (instancesDoNotTimeTravel &&
        (instancesAreNonCritical || readerHasToWait)) {
        return true;
    }

    return false;
}

// Check if a writer task instance can reach a reader task instance, detecting
// potential overwrites based on forward reachability.
bool mathframework::reach(PeriodicTaskInstance currentWriterTaskInstance,
                          PeriodicTaskInstance readerTaskInstance,
                          PeriodicTaskInstance nextWriterTaskInstance) {
    const bool readerInstanceIsReachable =
        forw(currentWriterTaskInstance, readerTaskInstance);
    const bool nextWriterInstanceCannotReachReaderInstance =
        !forw(nextWriterTaskInstance, readerTaskInstance);

    if (readerInstanceIsReachable &&
        nextWriterInstanceCannotReachReaderInstance) {
        return true;
    }

    return false;
}

// Determine if the entire timed path is reachable by checking the reachability
// of each consecutive pair of task instances.
bool mathframework::pathReach(
    const std::vector<PeriodicTaskInstance>& timedPath) {
    if (timedPath.empty()) {
        return false;
    }

    const std::size_t pathSize = timedPath.size();
    if (pathSize == 1) {
        return true;
    }

    for (std::size_t i = 0; i < pathSize - 1; i++) {
        const bool pathIsNotReachable =
            !reach(timedPath[i], timedPath[i + 1], timedPath[i].nextInstance());

        if (pathIsNotReachable) {
            return false;
        }
    }

    return true;
}
