#ifndef _TASK_CONSOLE_LOGGER_H_
#define _TASK_CONSOLE_LOGGER_H_

#include <io/logger/ILogger.h>

namespace e2e {
namespace io {

class SimplifiedConsoleLogger : public ILogger {
public:
    virtual void logValidInvalidPaths(
        const std::set<TimedPath>& allPathsSet,
        const std::set<TimedPath>& validPathSet,
        const std::set<TimedPath>& invalidPathSet) const override;

    virtual void logResults_LL(
        const std::optional<TimedPath>& maximumLatencyPath) const override;

    virtual void logResults_LF(
        const std::optional<TimedPath>& maximumLatencyPath) const override;

    virtual void logResults_FL(int maxFirstToLastPathDelay) const override;

    virtual void logResults_FF(int maxFirstToFirstPathDelay) const override;
};

}  // namespace io
}  // namespace e2e

#endif