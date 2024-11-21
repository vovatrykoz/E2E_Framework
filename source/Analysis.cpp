#include <Analysis.h>
#include <MathFramework.h>

std::set<TimedPath> analysis::removeUnreachablePaths(
    const std::set<TimedPath>& pathSet) {
    std::set<TimedPath> output;

    for (const auto& path : pathSet) {
        if (mathframework::pathReach(path.asVector())) {
            output.insert(path);
        }
    }

    return output;
}

std::set<TimedPath> analysis::removePathsProducingDublicateValues(
    const std::set<TimedPath>& pathSet) {
    std::set<TimedPath> output;

    int totalTaskCount = pathSet.size();
    for (const auto& currentPath : pathSet) {
        int counter = 0;
        for (const auto& otherPath : pathSet) {
            if (currentPath == otherPath) {
                counter++;
                continue;
            }

            bool pathInstancesHaveSameStart =
                (currentPath.firstTaskActivationTime() ==
                 otherPath.firstTaskActivationTime());

            bool currentInstanceFinishesLaterThanOther =
                (otherPath.lastTaskActivationTime() <
                 currentPath.lastTaskActivationTime());

            if (pathInstancesHaveSameStart &&
                currentInstanceFinishesLaterThanOther) {
                break;
            }

            counter++;
        }

        if (counter == totalTaskCount) {
            output.insert(currentPath);
        }
    }

    return output;
}

std::optional<TimedPath> analysis::getPathWithMaximumLatency(
    const std::set<TimedPath>& pathSet) {
    if (pathSet.empty()) {
        return std::nullopt;
    }

    auto maxLatencyIt = pathSet.begin();
    int maxLatency = maxLatencyIt->endToEndDelay();

    for (auto it = std::next(pathSet.begin()); it != pathSet.end(); it++) {
        int currentPathEndToEndDelay = it->endToEndDelay();

        if (currentPathEndToEndDelay > maxLatency) {
            maxLatency = currentPathEndToEndDelay;
            maxLatencyIt = it;
        }
    }

    return (*maxLatencyIt);
}

int analysis::getOverarchingDelay(const std::set<TimedPath>& pathSet) {
    int maxDelay = 0;

    for (const auto& currentPath : pathSet) {
        std::optional<TimedPath> predecessor =
            findPredecessor(currentPath, pathSet);

        int addend = 0;
        if (predecessor.has_value()) {
            addend = currentPath.firstTaskActivationTime() -
                     predecessor->firstTaskActivationTime();
        }

        int firstToLastDelay = currentPath.endToEndDelay() + addend;

        if (firstToLastDelay > maxDelay) {
            maxDelay = firstToLastDelay;
        }
    }

    return maxDelay;
}

std::optional<TimedPath> analysis::findPredecessor(
    const TimedPath& path, const std::set<TimedPath>& pathSet) {
    for (const auto& otherPath : pathSet) {
        if (path == otherPath) {
            continue;
        }

        if (path.succeeds(otherPath)) {
            return otherPath;
        }
    }

    return std::nullopt;
}
