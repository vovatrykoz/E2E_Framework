#include "TaskScheduling.h"

#include <numeric>

int scheduling::calculateLcmForEndToEndPath(
    const std::vector<Task>& endToEndPath) {
    if (endToEndPath.empty()) {
        return 0;
    }

    int acc = 1;
    for (const auto& task : endToEndPath) {
        acc = std::lcm(task.period, acc);
    }

    return acc;
}

std::vector<std::vector<TaskInstance>>
scheduling::generateTaskInstancesFromTasks(
    const std::vector<Task>& endToEndPath) {
    if (endToEndPath.empty()) {
        return std::vector<std::vector<TaskInstance>>();
    }

    std::vector<std::vector<TaskInstance>> result(endToEndPath.size());
    int lcm = scheduling::calculateLcmForEndToEndPath(endToEndPath);

    for (int i = 0; i < endToEndPath.size(); i++) {
        int instanceCount = lcm / endToEndPath[i].period;

        for (int j = 0; j < instanceCount; j++) {
            TaskInstance taskInstance(
                endToEndPath[i],
                endToEndPath[i].offset + endToEndPath[i].period * j);

            result[i].push_back(taskInstance);
        }
    }

    return result;
}

std::set<TimedPath> scheduling::generateTimedPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains) {
    std::set<TimedPath> result;
    if (taskInstanceChains.empty()) {
        return result;
    }

    int counter = 1;
    for (const auto& instanceChain : taskInstanceChains) {
        for (const auto& path : instanceChain) {
            std::string pathId = "#" + std::to_string(counter);
            result.insert(TimedPath(pathId, {path}));
            counter++;
        }
    }

    return result;
}

std::vector<std::vector<TaskInstance>> scheduling::buildTimedPaths(
    const std::vector<std::vector<TaskInstance>>& taskInstanceChains) {
    std::vector<std::vector<TaskInstance>> timedPaths;

    for (const auto& taskInstanceChain : taskInstanceChains) {
        timedPaths =
            scheduling::pathCartesianProduct(timedPaths, taskInstanceChain);
    }

    return timedPaths;
}

std::vector<std::vector<TaskInstance>> scheduling::pathCartesianProduct(
    const std::vector<std::vector<TaskInstance>>& timedPaths,
    const std::vector<TaskInstance>& taskInstanceChain) {
    std::vector<std::vector<TaskInstance>> product;

    if (timedPaths.empty()) {
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back({taskInstance});
        }

        return product;
    }

    for (const auto& timedPath : timedPaths) {
        for (const auto& taskInstance : taskInstanceChain) {
            product.push_back(timedPath);
            product.back().push_back(taskInstance);
        }
    }

    return product;
}
