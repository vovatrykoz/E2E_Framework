#include "io/logger/TextLogger.h"

#include <fstream>
#include <sstream>

using namespace e2e::io;

TextLogger::TextLogger(const std::string& pathToOutputFile)
    : pathToOutputFile(pathToOutputFile) {}

void TextLogger::logValidInvalidPaths(
    const std::set<TimedPath>& allPathsSet,
    const std::set<TimedPath>& validPathSet,
    const std::set<TimedPath>& invalidPathSet) const {
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

void TextLogger::logResults_LL(
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

void TextLogger::logResults_LF(
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

void TextLogger::logResults_FL(int maxFirstToLastPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-Last semantics:" << std::endl;

    output << "    Maximum path delay: " << maxFirstToLastPathDelay
           << std::endl;
    output << std::endl;

    this->writeOutputToFile(output.str());
}

void TextLogger::logResults_FF(int maxFirstToFirstPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-First semantics:" << std::endl;

    output << "    Maximum path delay: " << maxFirstToFirstPathDelay
           << std::endl;
    output << std::endl;

    this->writeOutputToFile(output.str());
}

void TextLogger::writeOutputToFile(const std::string& output) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Error: could not log data");
    }

    outFile << output;
    outFile.close();
}
