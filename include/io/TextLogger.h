#ifndef _TEXT_LOGGER_H_
#define _TEXT_LOGGER_H_

#include <TimedPath.h>

#include <optional>
#include <set>

class TextLogger {
public:
    TextLogger(const std::string& pathToOutputFile);

    void logResults(const std::set<TimedPath>& allPathsSet,
                    const std::set<TimedPath>& validPathSet,
                    const std::set<TimedPath>& invalidPathSet,
                    const std::optional<TimedPath>& maximumLatencyPath) const;

private:
    const std::string pathToOutputFile;
};

inline TextLogger::TextLogger(const std::string& pathToOutputFile)
    : pathToOutputFile(pathToOutputFile) {}

#endif