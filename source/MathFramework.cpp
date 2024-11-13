#include "MathFramework.h"

bool att(const TaskInstance& writerTask, const TaskInstance& readerTask) { 
    if(readerTask.activationTime < writerTask.activationTime) {
        return true;
    }

    return false;
}
