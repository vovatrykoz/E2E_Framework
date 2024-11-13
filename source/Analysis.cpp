#include <Analysis.h>

#include <MathFramework.h>

std::set<TimedPath> Analysis::removeUnreachablePaths(
    const std::set<TimedPath>& pathSet) {
    std::set<TimedPath> output;

    for(const auto& path : pathSet) {
        if(MathFramework::pathReach(path.asVector())) {
            output.emplace(path);
        }
    }

    return output;
}

int Analysis::calculateMaximumLatency(const std::set<TimedPath>& pathSet) {
    return 0;
}
