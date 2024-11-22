#ifndef _TASK_SCHEDULING_H_
#define _TASK_SCHEDULING_H_

#include <Task.h>

#include <vector>

namespace scheduling {

int calculateLcmForEndToEndPath(const std::vector<Task>& endToEndPath);

std::vector<std::vector<TaskInstance>> generateTaskInstancesFromTasks(
    const std::vector<Task>& endToEndPath);

}  // namespace scheduling

#endif