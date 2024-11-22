#ifndef _TASK_SCHEDULING_H_
#define _TASK_SCHEDULING_H_

#include <Task.h>
#include <TimedPath.h>

#include <set>
#include <vector>

namespace scheduling {

int calculateLcmForEndToEndPath(const std::vector<Task>& endToEndPath);

std::vector<std::vector<TaskInstance>> generateTaskInstancesFromTasks(
    const std::vector<Task>& endToEndPath);

std::set<TimedPath> generateTimedPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains);

}  // namespace scheduling

#endif