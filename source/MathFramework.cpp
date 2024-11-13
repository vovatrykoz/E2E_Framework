#include "MathFramework.h"

bool att(const TaskInstance& writerTask, const TaskInstance& readerTask) { 
    if(readerTask.activationTime < writerTask.activationTime) {
        return true;
    }

    return false;
}

bool crit(const TaskInstance& writerTask, const TaskInstance& readerTask) {
    int writerTaskTerminationTime = writerTask.activationTime + writerTask.wcet;

    if(readerTask.activationTime < writerTaskTerminationTime) {
        return true;
    }

    return false;
}
