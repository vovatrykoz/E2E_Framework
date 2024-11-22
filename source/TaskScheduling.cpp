#include "TaskScheduling.h"

#include <numeric>

using namespace e2e;

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
    const std::vector<std::vector<TaskInstance>>& timedPaths) {
    std::set<TimedPath> result;
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
