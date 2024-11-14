#ifndef _TEXT_LOGGER_H_
#define _TEXT_LOGGER_H_

#include <io/ILogger.h>

class TextLogger : public ILogger {
public:
    TextLogger(const std::string& pathToOutputFile);

    virtual void logValidInvalidPaths(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet) const override;

    virtual void logResults_LL(
        const std::optional<TimedPath>& maximumLatencyPath) const override;

    virtual void logResults_LF(
        const std::optional<TimedPath>& maximumLatencyPath) const override;

private:
    const std::string pathToOutputFile;

    void writeOutputToFile(const std::string& output) const ;
};

#endif