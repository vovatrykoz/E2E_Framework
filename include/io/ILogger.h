#ifndef _I_LOGGER_H_
#define _I_LOGGER_H_

#include <TimedPath.h>

#include <optional>
#include <set>

class ILogger {
public:
    virtual void logValidInvalidPaths(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet) const = 0;

    virtual void logResults_LL(
        const std::optional<TimedPath>& maximumLatencyPath) const = 0;

    virtual void logResults_LF(
        const std::optional<TimedPath>& maximumLatencyPath) const = 0;

    virtual void logResults_FL(int maxFirstToLastPathDelay) const = 0;

    virtual void logResults_FF(int maxFirstToFirstPathDelay) const = 0;

    virtual ~ILogger() = default;
};

#endif