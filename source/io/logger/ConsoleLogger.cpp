#include "io/logger/ConsoleLogger.h"

#include <chrono>
#include <iostream>

using namespace e2e::io;

void ConsoleLogger::logInfo(const std::string& infoMessage) const {
    std::cout << "(" << this->currentTime() << ") " << "INFO: " << infoMessage
              << "\n";
}

void ConsoleLogger::logWarning(const std::string& warningMessage) const {
    std::cout << "(" << this->currentTime() << ") "
              << "WARNING: " << warningMessage << "\n";
}

void ConsoleLogger::logError(const std::string& errorMessage) const {
    std::cerr << "(" << this->currentTime() << ") " << "ERROR: " << errorMessage
              << "\n";
}

void ConsoleLogger::logValidAndInvalidPaths(
    const std::multiset<TimedPath>& allPathsSet,
    const std::multiset<TimedPath>& validPathSet,
    const std::multiset<TimedPath>& invalidPathSet) const {
    std::cout << std::endl << "Results" << std::endl << std::endl;
    std::cout << "Number of analyzed paths: " << allPathsSet.size()
              << std::endl;

    std::cout << "Number of unreachable paths: " << invalidPathSet.size()
              << std::endl
              << std::endl;
    std::cout << "Unreachable paths: " << std::endl;
    for (const auto& invalidPath : invalidPathSet) {
        std::cout << invalidPath.name << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Number of reachable paths: " << validPathSet.size()
              << std::endl;
    std::cout << "Reachable paths: " << std::endl;
    for (const auto& validPath : validPathSet) {
        std::cout << validPath.name << std::endl;
    }

    std::cout << std::endl;
}

void ConsoleLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-Last semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Path with maximum latency over all reachable paths: "
                  << maximumLatencyPath->name << std::endl;

        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}

void ConsoleLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::cout << "Last-to-First semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        std::cout << "  Path with maximum latency over all reachable paths: "
                  << maximumLatencyPath->name << std::endl;

        std::cout << "  Maximum latency over all reachable paths: "
                  << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        std::cout << "  Maximum latency over all reachable paths: 0 (are "
                     "there any valid paths?)"
                  << std::endl;
    }

    std::cout << std::endl;
}

void ConsoleLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::cout << "First-to-Last semantics:" << std::endl;

    std::cout << "  Maximum path delay: " << maxFirstToLastPathDelay
              << std::endl;
    std::cout << std::endl;
}

void ConsoleLogger::logResults_FF(int maxFirstToFirstPathDelay) const {
    std::cout << "First-to-First semantics:" << std::endl;

    std::cout << "  Maximum path delay: " << maxFirstToFirstPathDelay
              << std::endl;
    std::cout << std::endl;
}

std::string ConsoleLogger::currentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_time_t);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
