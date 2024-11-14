#ifndef _I_LOGGER_H_
#define _I_LOGGER_H_

#include <TimedPath.h>

#include <optional>
#include <set>

class ILogger {
public:
    virtual void logResults(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet,
        const std::optional<TimedPath>& maximumLatencyPath) const = 0;
};

#endif