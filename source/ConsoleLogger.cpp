#include "ConsoleLogger.h"

#include <iostream>

void ConsoleLogger::logResults(const std::set<TimedPath>& allPathsSet,
                               const std::set<TimedPath>& validPathSet,
                               const std::set<TimedPath>& invalidPathSet,
                               int maximumLatency) {
    std::cout << std::endl << "Results" << std::endl;
    std::cout << "Number of analyzed paths: " << allPathsSet.size() << std::endl;

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

    std::cout << "Maximum latency over all reachable paths: " << maximumLatency
              << std::endl;
    std::cout << std::endl;
}