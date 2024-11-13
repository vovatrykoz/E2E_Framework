#include <Analysis.h>

#include <MathFramework.h>

std::set<TimedPath> analysis::removeUnreachablePaths(
    const std::set<TimedPath>& pathSet) {
    std::set<TimedPath> output;

    for(const auto& path : pathSet) {
        if(mathframework::pathReach(path.asVector())) {
            output.emplace(path);
        }
    }

    return output;
}

int analysis::calculateMaximumLatency(const std::set<TimedPath>& pathSet) {
    return 0;
}
