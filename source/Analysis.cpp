#include <Analysis.h>
#include <MathFramework.h>

#include <algorithm>

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
    auto maxLatencyIt =
        std::max_element(pathSet.begin(), pathSet.end(),
                         [](const TimedPath& a, const TimedPath& b) {
                             return a.endToEndDelay() < b.endToEndDelay();
                         });

    if (maxLatencyIt == pathSet.end()) {
        return std::nullopt;
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
    auto predecessorIt = std::find_if(
        pathSet.begin(), pathSet.end(), [path](const TimedPath& otherPath) {
            return path != otherPath && path.succeeds(otherPath);
        });

    if (predecessorIt == pathSet.end()) {
        return std::nullopt;
    }

    return (*predecessorIt);
}
