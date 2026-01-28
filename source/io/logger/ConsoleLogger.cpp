#include <e2e/io/logger/ConsoleLogger.h>

#include <chrono>
#include <iostream>

using namespace e2e::io;

void ConsoleLogger::logValidAndInvalidPaths(
    const std::vector<TimedPath>& allPathsSet,
    const std::vector<TimedPath>& validPathSet,
    const std::vector<TimedPath>& invalidPathSet) const {
    std::cout << "\n" << "Results" << "\n" << "\n";
    std::cout << "Number of analyzed paths: " << allPathsSet.size() << "\n";

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << "\n"
              << "\n";
    std::cout << "Unreachable paths: " << "\n";
    for (const auto& invalidPath : invalidPathSet) {
        std::cout << invalidPath.name << "\n";
    }

    std::cout << "\n";

    std::cout << "Number of reachable paths: " << validPathSet.size() << "\n";
    std::cout << "Reachable paths: " << "\n";
    for (const auto& validPath : validPathSet) {
        std::cout << validPath.name << "\n";
    }

    std::cout << "\n";
}

void ConsoleLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-Last semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Path with maximum latency over all reachable paths: "
                  << maximumLatencyPath->name << "\n";

        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << "\n";
    }

    std::cout << "\n";
}

void ConsoleLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-First semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Path with maximum latency over all reachable paths: "
                  << maximumLatencyPath->name << "\n";

        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << "\n";
    }

    std::cout << "\n";
}

void ConsoleLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::cout << "First-to-Last semantics:" << "\n";

    std::cout << "  Maximum path delay: " << maxFirstToLastPathDelay << "\n";
    std::cout << "\n";
}

void ConsoleLogger::logResults_FF(int maxFirstToFirstPathDelay) const {
    std::cout << "First-to-First semantics:" << "\n";

    std::cout << "  Maximum path delay: " << maxFirstToFirstPathDelay << "\n";
    std::cout << "\n";
}
