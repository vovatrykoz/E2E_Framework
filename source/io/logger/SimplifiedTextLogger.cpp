#include <e2e/io/logger/SimplifiedPlainTextLogger.h>

#include <chrono>
#include <fstream>
#include <sstream>

using namespace e2e::io;

SimplifiedPlainTextLogger::SimplifiedPlainTextLogger(
    const std::string& pathToOutputFile)
    : pathToOutputFile(pathToOutputFile) {}

void SimplifiedPlainTextLogger::logValidAndInvalidPaths(
    const std::vector<TimedPath>& allPathsSet,
    const std::vector<TimedPath>& validPathSet,
    const std::vector<TimedPath>& invalidPathSet) const {
    std::stringstream output;

    output << "Results" << "\n" << "\n";
    output << "- Number of analyzed paths: " << allPathsSet.size() << "\n";

    output << "\n";

    output << "- Number of unreachable paths: " << invalidPathSet.size()
           << "\n";

    output << "\n";

    output << "- Number of reachable paths: " << validPathSet.size() << "\n";

    output << "\n";

    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    this->writeOutputToFile(output.str());
}

void SimplifiedPlainTextLogger::logResults_LL(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::stringstream output;

    output << "- Last-to-Last semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        output << "    Maximum latency over all reachable paths: "
               << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        output << "    Maximum latency over all reachable paths: 0 (are "
                  "there any valid paths?)"
               << "\n";
    }

    output << "\n";

    this->writeOutputToFile(output.str());
}

void SimplifiedPlainTextLogger::logResults_LF(
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::stringstream output;

    output << "- Last-to-First semantics:" << "\n";

    if (maximumLatencyPath.has_value()) {
        output << "    Maximum latency over all reachable paths: "
               << maximumLatencyPath->endToEndDelay() << "\n";
    } else {
        output << "    Maximum latency over all reachable paths: 0 (are "
                  "there any valid paths?)"
               << "\n";
    }

    output << "\n";

    this->writeOutputToFile(output.str());
}

void SimplifiedPlainTextLogger::logResults_FL(
    int maxFirstToLastPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-Last semantics:" << "\n";

    output << "    Maximum path delay: " << maxFirstToLastPathDelay << "\n";
    output << "\n";

    this->writeOutputToFile(output.str());
}

void SimplifiedPlainTextLogger::logResults_FF(
    int maxFirstToFirstPathDelay) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);
    std::stringstream output;

    output << "- First-to-First semantics:" << "\n";

    output << "    Maximum path delay: " << maxFirstToFirstPathDelay << "\n";
    output << "\n";

    this->writeOutputToFile(output.str());
}

void SimplifiedPlainTextLogger::writeOutputToFile(
    const std::string& output) const {
    std::ofstream outFile(this->pathToOutputFile, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Error: could not log data");
    }

    outFile << output;
    outFile.close();
}
