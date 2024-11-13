#include <Analysis.h>

#include <MathFramework.h>

std::set<TimedPath> analysis::removeUnreachablePaths(
    const std::set<TimedPath>& pathSet) {
    std::set<TimedPath> output;

    for(const auto& path : pathSet) {
        if(mathframework::pathReach(path.asVector())) {
            output.insert(path);
        }
    }

    return output;
}

int analysis::calculateMaximumLatency(const std::set<TimedPath>& pathSet) {
    int max = 0;

    for(const auto& path : pathSet) {
        int pathEndToEnd = path.endToEndDelay();

        if(pathEndToEnd > max) {
            max = pathEndToEnd;
        }
    }

    return max;
}
