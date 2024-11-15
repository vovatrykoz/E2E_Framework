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

std::set<TimedPath> analysis::removeDublicatesWithSameStart(
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
    int max = 0;

    for (auto it = pathSet.begin(); it != pathSet.end(); it++) {
        const TimedPath& path = (*it);
        int pathEndToEnd = path.endToEndDelay();

        if (pathEndToEnd > max) {
            max = pathEndToEnd;
            maxLatencyIt = it;
        }
    }

    return (*maxLatencyIt);
}

int analysis::getFirstToLastPathDelay(const std::set<TimedPath>& pathSet) {
    int max = 0;

    for (const auto& currentPath : pathSet) {
        std::optional<TimedPath> predecessor =
            findPredecessor(currentPath, pathSet);

        int predecessorActivationTime = 0;
        if (predecessor.has_value()) {
            predecessorActivationTime =
                predecessor.value().firstTaskActivationTime();
        }

        int firstToLastDelay = currentPath.endToEndDelay() +
                               currentPath.firstTaskActivationTime() -
                               predecessorActivationTime;

        if (firstToLastDelay > max) {
            max = firstToLastDelay;
        }
    }

    return max;
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
