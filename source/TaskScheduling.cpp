#include "TaskScheduling.h"

#include <numeric>

using namespace e2e;

// Calculates the least common multiple (LCM) of the periods of tasks in the
// path
int scheduling::calculateLcmForEndToEndPath(
    const std::vector<OffsetPeriodicTask>& endToEndPath) {
    // Return 0 if the path is empty, as there's no LCM to calculate
    if (endToEndPath.empty()) {
        return 0;
    }

    int acc = 1;
    // Calculate the LCM of all task periods
    for (const auto& task : endToEndPath) {
        acc = std::lcm(task.baseTask.period, acc);
    }

    return acc;
}

// Generates task instances for each task in the path based on their periods and
// offsets
std::vector<std::vector<PeriodicTaskInstance>>
scheduling::generateTaskInstancesFromPath(
    const std::vector<OffsetPeriodicTask>& endToEndPath) {
    if (endToEndPath.empty()) {
        // empty vector
        return std::vector<std::vector<PeriodicTaskInstance>>();
    }

    std::vector<std::vector<PeriodicTaskInstance>> result(endToEndPath.size());
    const int lcm = scheduling::calculateLcmForEndToEndPath(endToEndPath);

    // Generate task instances for each task in the path
    for (int i = 0; i < endToEndPath.size(); i++) {
        int instanceCount = lcm / endToEndPath[i].baseTask.period;

        // Generate each task instance based on offset and period
        for (int j = 0; j < instanceCount; j++) {
            const PeriodicTaskInstance taskInstance(
                endToEndPath[i].baseTask,
                endToEndPath[i].offset + endToEndPath[i].baseTask.period * j);

            result[i].push_back(taskInstance);
        }
    }

    return result;
}

// Generates timed paths from the task instances, each with a unique path ID
std::multiset<TimedPath> scheduling::generateTimedPathsFromInstances(
    const std::vector<std::vector<PeriodicTaskInstance>>& timedPaths) {
    std::multiset<TimedPath> result;
    if (timedPaths.empty()) {
        // empty multiset
        return result;
    }

    int counter = 1;
    // Insert each timed path into the multiset with a unique path ID
    for (const auto& instanceChain : timedPaths) {
        const std::string pathId = "#" + std::to_string(counter);
        result.insert(TimedPath(pathId, instanceChain));
        counter++;
    }

    return result;
}

// Builds execution paths by chaining together task instances from the input
// chains
std::vector<std::vector<PeriodicTaskInstance>>
scheduling::buildTaskExecutionPaths(
    const std::vector<std::vector<PeriodicTaskInstance>>& taskInstanceChains) {
    std::vector<std::vector<PeriodicTaskInstance>> timedPaths;

    // Compute the Cartesian product of task instance chains to build execution
    // paths
    for (const auto& taskInstanceChain : taskInstanceChains) {
        timedPaths = scheduling::cartesianProductOfTimedPaths(
            timedPaths, taskInstanceChain);
    }

    return timedPaths;
}

// Computes the Cartesian product of timed paths and a task instance chain
std::vector<std::vector<PeriodicTaskInstance>>
scheduling::cartesianProductOfTimedPaths(
    const std::vector<std::vector<PeriodicTaskInstance>>& timedPaths,
    const std::vector<PeriodicTaskInstance>& taskInstanceChain) {
    std::vector<std::vector<PeriodicTaskInstance>> product;

    // If timedPaths is empty, return taskInstanceChain as the product
    if (timedPaths.empty()) {
        product.reserve(taskInstanceChain.size());
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back({taskInstance});
        }
        return product;
    }

    // Otherwise, calculate the Cartesian product
    product.reserve(timedPaths.size() * taskInstanceChain.size());

    // Combine each task instance in timedPaths with each task instance in
    // taskInstanceChain
    for (const auto& timedPath : timedPaths) {
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back(timedPath);
            product.back().push_back(taskInstance);
        }
    }

    return product;
}
