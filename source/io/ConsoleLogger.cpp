#include "io/ConsoleLogger.h"

#include <iostream>

void ConsoleLogger::logValidInvalidPaths(
    const std::set<TimedPath>& allPathsSet,
    const std::set<TimedPath>& validPathSet,
    const std::set<TimedPath>& invalidPathSet) const {
    std::cout << std::endl << "Results" << std::endl << std::endl;
    std::cout << "Number of analyzed paths: " << allPathsSet.size()
              << std::endl;

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << std::endl;
    std::cout << "Unreachable paths: " << std::endl;
    for (const auto& invalidPath : invalidPathSet) {
        std::cout << invalidPath.name() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Number of reachable paths: " << validPathSet.size()
              << std::endl;
    std::cout << "Reachable paths: " << std::endl;
    for (const auto& validPath : validPathSet) {
        std::cout << validPath.name() << std::endl;
    }

    std::cout << std::endl;
}
void ConsoleLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    if (maximumLatencyPath.has_value()) {
        std::cout << "Path with maximum latency over all reachable paths using "
                     "Last-to-Last semantics: "
                  << maximumLatencyPath.value().name() << std::endl;

        std::cout << "Maximum latency over all reachable paths using "
                     "Last-to-Last semantics: "
                  << maximumLatencyPath.value().endToEndDelay() << std::endl;
    } else {
        std::cout << "Maximum latency over all reachable paths using "
                     "Last-to-Last semantics: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}

void ConsoleLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    if (maximumLatencyPath.has_value()) {
        std::cout << "Path with maximum latency over all reachable paths using "
                     "Last-to-First semantics: "
                  << maximumLatencyPath.value().name() << std::endl;

        std::cout << "Maximum latency over all reachable paths using "
                     "Last-to-First semantics: "
                  << maximumLatencyPath.value().endToEndDelay() << std::endl;
    } else {
        std::cout << "Maximum latency over all reachable paths using "
                     "Last-to-First semantics: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}
