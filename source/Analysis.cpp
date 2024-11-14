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

std::optional<TimedPath> analysis::getPathWithMaximumLatency(const std::set<TimedPath>& pathSet) {
    if(pathSet.empty()) {
        return std::nullopt;
    }
    
    auto maxLatencyIt = pathSet.begin();
    int max = 0;

    for (auto it = pathSet.begin(); it != pathSet.end(); it++) {
        const TimedPath& path = (*it);
        int pathEndToEnd = path.endToEndDelay();

        if(pathEndToEnd > max) {
            max = pathEndToEnd;
            maxLatencyIt = it;
        }
    }

    return (*maxLatencyIt);
}
