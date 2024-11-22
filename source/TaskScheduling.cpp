#include "TaskScheduling.h"

#include <numeric>

int scheduling::calculateLcmForEndToEndPath(
    const std::vector<Task>& endToEndPath) {
    if (endToEndPath.empty()) {
        return 0;
    }

    int acc = 1;
    for(const auto& task : endToEndPath) {
        acc = std::lcm(task.period, acc);
    }

    return acc;
}