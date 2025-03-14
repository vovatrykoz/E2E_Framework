#include <Analysis.h>
#include <MathFramework.h>

#include <algorithm>

using namespace e2e;

// Check if the path is reachable according to the conditions defined in
// MathFramework.
std::multiset<TimedPath> analysis::removeUnreachablePaths(
    const std::multiset<TimedPath>& pathSet) {
    std::multiset<TimedPath> output;

    for (const auto& path : pathSet) {
        if (mathframework::pathReach(path.asVector())) {
            output.insert(path);
        }
    }

    return output;
}

// Iterate through all paths and check if they produce duplicate values due to
// identical start time. A path is considered duplicate if it finishes later
// than another path with the same start time.
std::multiset<TimedPath> analysis::removePathsProducingDuplicateValues(
    const std::multiset<TimedPath>& pathSet) {
    std::multiset<TimedPath> output;

    for (const auto& currentPath : pathSet) {
        bool isDuplicate = false;

        for (const auto& otherPath : pathSet) {
            if (currentPath == otherPath) {
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
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            output.insert(currentPath);
        }
    }

    return output;
}

// Find the path with the maximum end-to-end latency by comparing paths in the
// set.
std::optional<TimedPath> analysis::getPathWithMaximumLatency(
    const std::multiset<TimedPath>& pathSet) {
    const auto maxLatencyIt =
        std::max_element(pathSet.begin(), pathSet.end(),
                         [](const TimedPath& a, const TimedPath& b) {
                             return a.endToEndDelay() < b.endToEndDelay();
                         });

    if (maxLatencyIt == pathSet.end()) {
        return std::nullopt;
    }

    return (*maxLatencyIt);
}

// For each path, calculate the delay between the current path and its
// predecessor, then compute the overall maximum delay.
int analysis::getOverarchingDelay(const std::multiset<TimedPath>& pathSet) {
    int maxDelay = 0;

    for (const auto& currentPath : pathSet) {
        std::optional<TimedPath> predecessor =
            findPredecessor(currentPath, pathSet);

        int delayAdjustment = 0;
        if (predecessor.has_value()) {
            delayAdjustment = currentPath.firstTaskActivationTime() -
                              predecessor->firstTaskActivationTime();
        }

        int firstToLastDelay = currentPath.endToEndDelay() + delayAdjustment;

        maxDelay = std::max(maxDelay, firstToLastDelay);
    }

    return maxDelay;
}

// Find the predecessor of the current path, which is a path that ends before
// the current path starts.
std::optional<TimedPath> analysis::findPredecessor(
    const TimedPath& path, const std::multiset<TimedPath>& pathSet) {
    const auto predecessorIt = std::find_if(
        pathSet.begin(), pathSet.end(), [&path](const TimedPath& otherPath) {
            return path != otherPath && path.succeeds(otherPath);
        });

    if (predecessorIt == pathSet.end()) {
        return std::nullopt;
    }

    return (*predecessorIt);
}
