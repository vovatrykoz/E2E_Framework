#ifndef _SIMPLIFIED_CONSOLE_LOGGER_H_
#define _SIMPLIFIED_CONSOLE_LOGGER_H_

#include <e2e/io/logger/IResultLogger.h>

namespace e2e {
namespace io {

class SimplifiedConsoleLogger : public IResultLogger {
   public:
    virtual void logValidAndInvalidPaths(
        const std::multiset<TimedPath>& allPathsSet,
        const std::multiset<TimedPath>& validPathSet,
        const std::multiset<TimedPath>& invalidPathSet) const override;

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