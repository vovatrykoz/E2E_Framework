#ifndef _TASK_SCHEDULING_H_
#define _TASK_SCHEDULING_H_

#include <Task.h>
#include <TimedPath.h>

#include <set>
#include <vector>

namespace e2e {
namespace scheduling {

int calculateLcmForEndToEndPath(const std::vector<Task>& endToEndPath);

std::vector<std::vector<TaskInstance>> generateTaskInstancesFromTasks(
    const std::vector<Task>& endToEndPath);

std::set<TimedPath> generateTimedPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains);

std::vector<std::vector<TaskInstance>> buildTimedPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains);

std::vector<std::vector<TaskInstance>> pathCartesianProduct(
    const std::vector<std::vector<TaskInstance>>& timedPaths,
    const std::vector<TaskInstance>& taskInstanceChain);

}  // namespace scheduling
}  // namespace e2e

#endif