#include <Analysis.h>
#include <io/ConsoleLogger.h>
#include <io/InputReader.h>
#include <io/SimpleTextReader.h>
#include <io/TextLogger.h>

#include <iostream>
#include <limits>
#include <optional>

int main(void) {
    SimpleTextReader textInputReader("../paths.txt");
    TextLogger textLogger("../results.txt");
    InputReader inputReader;
    ConsoleLogger logger;

    // read user input
    std::set<TimedPath> pathSet;

    try {
        pathSet = textInputReader.readPathsSet();
    } catch (std::runtime_error err) {
        std::cerr << "Failed to load timed path! " << err.what() << std::endl;
    }

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
    try {
        textLogger.logResults(pathSet, validPathSet, invalidPathSet,
                              maximumLatencyPath);
    } catch (std::runtime_error err) {
        std::cerr << "Failed to log results! " << err.what() << std::endl;
    }

    return 0;
}