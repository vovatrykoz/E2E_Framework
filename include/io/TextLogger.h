#ifndef _TEXT_LOGGER_H_
#define _TEXT_LOGGER_H_

#include <io/ILogger.h>

class TextLogger : public ILogger {
public:
    TextLogger(const std::string& pathToOutputFile);

    virtual void logResults(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet,
        const std::optional<TimedPath>& maximumLatencyPath) const override;

private:
    const std::string pathToOutputFile;
};

#endif