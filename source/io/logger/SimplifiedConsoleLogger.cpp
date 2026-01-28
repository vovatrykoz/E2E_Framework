#include <e2e/io/logger/SimplifiedConsoleLogger.h>

#include <chrono>
#include <iostream>

using namespace e2e::io;

void SimplifiedConsoleLogger::logValidAndInvalidPaths(
    const std::vector<TimedPath>& allPathsSet,
    const std::vector<TimedPath>& validPathSet,
    const std::vector<TimedPath>& invalidPathSet) const {
    std::cout << "\n" << "Results" << "\n" << "\n";
    std::cout << "Number of analyzed paths: " << allPathsSet.size() << "\n";

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << "\n"
              << "\n";

    std::cout << "\n";

    std::cout << "Number of reachable paths: " << validPathSet.size() << "\n";

    std::cout << "\n";
}

void SimplifiedConsoleLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-Last semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << "\n";
    }

    std::cout << "\n";
}

void SimplifiedConsoleLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-First semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << "\n";
    }

    std::cout << "\n";
}

void SimplifiedConsoleLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::cout << "First-to-Last semantics:" << "\n";

    std::cout << "  Maximum path delay: " << maxFirstToLastPathDelay << "\n";
    std::cout << "\n";
}

void SimplifiedConsoleLogger::logResults_FF(
    int maxFirstToFirstPathDelay) const {
    std::cout << "First-to-First semantics:" << "\n";

    std::cout << "  Maximum path delay: " << maxFirstToFirstPathDelay << "\n";
    std::cout << "\n";
}
