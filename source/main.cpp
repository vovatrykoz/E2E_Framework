#include <Analysis.h>
#include <io/ConsoleLogger.h>
#include <io/InputReader.h>
#include <io/SimpleTextReader.h>

#include <iostream>
#include <limits>
#include <optional>

int main(void) {
    SimpleTextReader textInputReader("../paths.txt");
    InputReader inputReader;
    ConsoleLogger logger;

    textInputReader.readPathsSet();

    // read user input
    std::set<TimedPath> pathSet = inputReader.readPathsSet();

    // perform the analysis
    std::set<TimedPath> validPathSet =
        analysis::removeUnreachablePaths(pathSet);
    std::optional<TimedPath> maximumLatencyPath =
        analysis::getPathWithMaximumLatency(validPathSet);

    // idenrify which paths turned out to be invalid
    std::set<TimedPath> invalidPathSet;
    for (const auto& path : pathSet) {
        if (validPathSet.find(path) == validPathSet.end()) {
            invalidPathSet.insert(path);
        }
    }

    // log results
    logger.logResults(pathSet, validPathSet, invalidPathSet,
                      maximumLatencyPath);

    return 0;
}