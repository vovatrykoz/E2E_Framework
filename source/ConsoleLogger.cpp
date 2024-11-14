#include "ConsoleLogger.h"

#include <iostream>

void ConsoleLogger::logResults(
    const std::set<TimedPath>& allPathsSet,
    const std::set<TimedPath>& validPathSet,
    const std::set<TimedPath>& invalidPathSet,
    const std::optional<TimedPath>& maximumLatencyPath) {
    std::cout << std::endl << "Results" << std::endl;
    std::cout << "Number of analyzed paths: " << allPathsSet.size()
              << std::endl;

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << std::endl;
    std::cout << "Unreachable paths: " << std::endl;
    for (const auto& invalidPath : invalidPathSet) {
        std::cout << invalidPath.getName() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Number of reachable paths: " << validPathSet.size()
              << std::endl;
    std::cout << "Reachable paths: " << std::endl;
    for (const auto& validPath : validPathSet) {
        std::cout << validPath.getName() << std::endl;
    }

    std::cout << std::endl;

    if (maximumLatencyPath.has_value()) {
        std::cout << "Path with maximum latency over all reachable paths: "
                  << maximumLatencyPath.value().getName() << std::endl;

        std::cout << "Maximum latency over all reachable paths: "
                  << maximumLatencyPath.value().endToEndDelay() << std::endl;
    } else {
        std::cout << "Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}