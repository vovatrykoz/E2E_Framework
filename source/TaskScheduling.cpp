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
