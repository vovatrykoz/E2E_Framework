#include "io/logger/TaskConsoleLogger.h"

#include <iostream>

using namespace e2e::io;

void TaskConsoleLogger::logValidInvalidPaths(
    const std::set<TimedPath>& allPathsSet,
    const std::set<TimedPath>& validPathSet,
    const std::set<TimedPath>& invalidPathSet) const {
    std::cout << std::endl << "Results" << std::endl << std::endl;
    std::cout << "Number of analyzed paths: " << allPathsSet.size()
              << std::endl;

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << std::endl
              << std::endl;

    std::cout << std::endl;

    std::cout << "Number of reachable paths: " << validPathSet.size()
              << std::endl;

    std::cout << std::endl;
}

void TaskConsoleLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-Last semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}

void TaskConsoleLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-First semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}

void TaskConsoleLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::cout << "First-to-Last semantics:" << std::endl;

    std::cout << "  Maximum path delay: " << maxFirstToLastPathDelay
              << std::endl;
    std::cout << std::endl;
}

void TaskConsoleLogger::logResults_FF(int maxFirstToFirstPathDelay) const {
    std::cout << "First-to-First semantics:" << std::endl;

    std::cout << "  Maximum path delay: " << maxFirstToFirstPathDelay
              << std::endl;
    std::cout << std::endl;
}
