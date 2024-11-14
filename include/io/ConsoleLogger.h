#ifndef _CONSOLE_LOGGER_H_
#define _CONSOLE_LOGGER_H_

#include <io/ILogger.h>

class ConsoleLogger : public ILogger {
public:
    virtual void logResults(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet,
        const std::optional<TimedPath>& maximumLatencyPath) const override;
};

#endif