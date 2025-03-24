#include <fstream>
#include <sstream>

#include "io/logger/PlainTextLogger.h"

using namespace e2e::io;

PlainTextLogger::PlainTextLogger(const std::string& pathToOutputFile)
    : pathToOutputFile(pathToOutputFile) {}

void PlainTextLogger::logInfo(const std::string& infoMessage) const {
    std::stringstream output;
    output << "INFO: " << infoMessage << "\n";

    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logWarning(const std::string& warningMessage) const {
    std::stringstream output;
    output << "WARNING: " << warningMessage << "\n";

    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logError(const std::string& errorMessage) const {
    std::stringstream output;
    output << "ERROR: " << errorMessage << "\n";

    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logValidAndInvalidPaths(
    const std::multiset<TimedPath>& allPathsSet,
    const std::multiset<TimedPath>& validPathSet,
    const std::multiset<TimedPath>& invalidPathSet) const {
    std::stringstream output;

    output << "Results" << std::endl << std::endl;
    output << "- Number of analyzed paths: " << allPathsSet.size() << std::endl;

    output << std::endl;

    output << "- Number of unreachable paths: " << invalidPathSet.size()
           << std::endl;
    output << "Unreachable paths: " << std::endl;
    for (const auto& invalidPath : invalidPathSet) {
        output << invalidPath.name << std::endl;
    }

    output << std::endl;

    output << "- Number of reachable paths: " << validPathSet.size()
           << std::endl;
    output << "Reachable paths: " << std::endl;
    for (const auto& validPath : validPathSet) {
        output << validPath.name << std::endl;
    }

    output << std::endl;

    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::stringstream output;

    output << "- Last-to-Last semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        output << "    Path with maximum latency over all reachable paths: "
               << maximumLatencyPath->name << std::endl;

        output << "    Maximum latency over all reachable paths"
               << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        output << "    Maximum latency over all reachable paths: 0 (are "
                  "there any valid paths?)"
               << std::endl;
    }

    output << std::endl;

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::stringstream output;

    output << "- Last-to-First semantics:" << std::endl;

    if (maximumLatencyPath.has_value()) {
        output << "    Path with maximum latency over all reachable paths: "
               << maximumLatencyPath->name << std::endl;

        output << "    Maximum latency over all reachable paths: "
               << maximumLatencyPath->endToEndDelay() << std::endl;
    } else {
        output << "    Maximum latency over all reachable paths: 0 (are "
                  "there any valid paths?)"
               << std::endl;
    }

    output << std::endl;

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-Last semantics:" << std::endl;

    output << "    Maximum path delay: " << maxFirstToLastPathDelay
           << std::endl;
    output << std::endl;

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::logResults_FF(int maxFirstToFirstPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-First semantics:" << std::endl;

    output << "    Maximum path delay: " << maxFirstToFirstPathDelay
           << std::endl;
    output << std::endl;

    this->writeOutputToFile(output.str());
}

void PlainTextLogger::writeOutputToFile(const std::string& output) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Error: could not log data");
    }

    outFile << output;
    outFile.close();
}
