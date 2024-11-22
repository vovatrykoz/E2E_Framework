#ifndef _TASK_SCHEDULING_H_
#define _TASK_SCHEDULING_H_

#include <Task.h>
#include <TimedPath.h>

#include <set>
#include <vector>

namespace e2e {
namespace scheduling {

/**
 * @brief Calculates the least common multiple (LCM) for a task path.
 *
 * This function computes the least common multiple (LCM) of the periods of all
 * the tasks in the provided task path. The LCM is useful in scheduling
 * algorithms, particularly for determining the interval after which the tasks
 * will repeat their execution.
 *
 * @param taskPath A vector of tasks representing the task path.
 *
 * @return The least common multiple of the periods of the tasks in the path.
 */
int calculateLcmForEndToEndPath(const std::vector<Task>& endToEndPath);

/**
 * @brief Generates task instances from a task path.
 *
 * This function generates task instances for each task in the provided task
 * path. Each task instance has a specific activation time based on the task's
 * period and offset.
 *
 * @param taskPath A vector of tasks that define the task path.
 *
 * @return A vector of vectors, where each inner vector contains task instances
 * for each task in the path.
 */
std::vector<std::vector<TaskInstance>> generateTaskInstancesFromPath(
    const std::vector<Task>& taskPath);

/**
 * @brief Generates timed paths from task instances.
 *
 * This function takes a set of task instance chains and generates corresponding
 * timed paths. A timed path is a sequence of task instances with their
 * activation times.
 *
 * @param taskInstanceChains A vector of vectors of task instances.
 *
 * @return A set of timed paths, where each path is a sequence of task instances
 * with specific activation times.
 */
std::set<TimedPath> generateTimedPathsFromInstances(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains);

/**
 * @brief Builds execution paths from task instance chains.
 *
 * This function constructs execution paths by chaining together task instances
 * based on the provided task instance chains. The result is a set of paths that
 * represent the execution order of tasks over time.
 *
 * @param taskInstanceChains A vector of vectors of task instances.
 *
 * @return A vector of vectors, each representing an execution path of task
 * instances.
 */
std::vector<std::vector<TaskInstance>> buildTaskExecutionPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains);

/**
 * @brief Computes the Cartesian product of timed paths.
 *
 * This function calculates the Cartesian product of the provided timed paths
 * with a specific task instance chain, generating all possible combinations of
 * timed paths from both inputs.
 *
 * @param timedPaths A vector of vectors of task instances, representing the
 * timed paths.
 * @param taskInstanceChain A vector of task instances to combine with the timed
 * paths.
 *
 * @return A vector of vectors, where each inner vector represents a combination
 * of timed paths and task instances from the input.
 */
std::vector<std::vector<TaskInstance>> cartesianProductOfTimedPaths(
    const std::vector<std::vector<TaskInstance>>& timedPaths,
    const std::vector<TaskInstance>& taskInstanceChain);

}  // namespace scheduling
}  // namespace e2e

#endif