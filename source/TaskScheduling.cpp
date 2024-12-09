#include "TaskScheduling.h"

#include <numeric>

using namespace e2e;

int scheduling::calculateLcmForEndToEndPath(
    const std::vector<PeriodicTask>& endToEndPath) {
    if (endToEndPath.empty()) {
        return 0;
    }

    int acc = 1;
    for (const auto& task : endToEndPath) {
        acc = std::lcm(task.period, acc);
    }

    return acc;
}

std::vector<std::vector<PeriodicTaskInstance>>
scheduling::generateTaskInstancesFromPath(
    const std::vector<PeriodicTask>& endToEndPath) {
    if (endToEndPath.empty()) {
        return std::vector<std::vector<PeriodicTaskInstance>>();
    }

    std::vector<std::vector<PeriodicTaskInstance>> result(endToEndPath.size());
    int lcm = scheduling::calculateLcmForEndToEndPath(endToEndPath);

    for (int i = 0; i < endToEndPath.size(); i++) {
        int instanceCount = lcm / endToEndPath[i].period;

        for (int j = 0; j < instanceCount; j++) {
            PeriodicTaskInstance taskInstance(
                endToEndPath[i],
                endToEndPath[i].offset + endToEndPath[i].period * j);

            result[i].push_back(taskInstance);
        }
    }

    return result;
}

std::multiset<TimedPath> scheduling::generateTimedPathsFromInstances(
    const std::vector<std::vector<PeriodicTaskInstance>>& timedPaths) {
    std::multiset<TimedPath> result;
    if (timedPaths.empty()) {
        return result;
    }

    int counter = 1;
    for (const auto& instanceChain : timedPaths) {
        std::string pathId = "#" + std::to_string(counter);
        result.insert(TimedPath(pathId, instanceChain));
        counter++;
    }

    return result;
}

std::vector<std::vector<PeriodicTaskInstance>>
scheduling::buildTaskExecutionPaths(
    const std::vector<std::vector<PeriodicTaskInstance>>& taskInstanceChains) {
    std::vector<std::vector<PeriodicTaskInstance>> timedPaths;

    for (const auto& taskInstanceChain : taskInstanceChains) {
        timedPaths = scheduling::cartesianProductOfTimedPaths(
            timedPaths, taskInstanceChain);
    }

    return timedPaths;
}

std::vector<std::vector<PeriodicTaskInstance>>
scheduling::cartesianProductOfTimedPaths(
    const std::vector<std::vector<PeriodicTaskInstance>>& timedPaths,
    const std::vector<PeriodicTaskInstance>& taskInstanceChain) {
    std::vector<std::vector<PeriodicTaskInstance>> product;

    if (timedPaths.empty()) {
        product.reserve(taskInstanceChain.size());
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back({taskInstance});
        }

        return product;
    }

    product.reserve(timedPaths.size() * taskInstanceChain.size());

    for (const auto& timedPath : timedPaths) {
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back(timedPath);
            product.back().push_back(taskInstance);
        }
    }

    return product;
}
