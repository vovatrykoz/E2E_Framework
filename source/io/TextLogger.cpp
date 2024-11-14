#include "io/TextLogger.h"

#include <fstream>
#include <sstream>

TextLogger::TextLogger(const std::string& pathToOutputFile)
    : pathToOutputFile(pathToOutputFile) {}

void TextLogger::logResults(
    const std::set<TimedPath>& allPathsSet,
    const std::set<TimedPath>& validPathSet,
    const std::set<TimedPath>& invalidPathSet,
    const std::optional<TimedPath>& maximumLatencyPath) const {
    std::stringstream output;

    output << "Results" << std::endl << std::endl;
    output << "Number of analyzed paths: " << allPathsSet.size() << std::endl;

    output << "Number of unreachable paths: " << invalidPathSet.size()
           << std::endl;
    output << "Unreachable paths: " << std::endl;
    for (const auto& invalidPath : invalidPathSet) {
        output << invalidPath.name() << std::endl;
    }

    output << std::endl;

    output << "Number of reachable paths: " << validPathSet.size() << std::endl;
    output << "Reachable paths: " << std::endl;
    for (const auto& validPath : validPathSet) {
        output << validPath.name() << std::endl;
    }

    output << std::endl;

    if (maximumLatencyPath.has_value()) {
        output << "Path with maximum latency over all reachable paths: "
               << maximumLatencyPath.value().name() << std::endl;

        output << "Maximum latency over all reachable paths: "
               << maximumLatencyPath.value().endToEndDelay() << std::endl;
    } else {
        output << "Maximum latency over all reachable paths: 0 (are "
                  "there any valid paths?)"
               << std::endl;
    }

    std::ofstream outFile(this->pathToOutputFile);

    if (!outFile.is_open()) {
        throw std::runtime_error("Error: could not log data");
    }

    outFile << output.str();
    outFile.close();
}