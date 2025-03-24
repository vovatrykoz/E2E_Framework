#ifndef _PLAIN_TEXT_LOGGER_H_
#define _PLAIN_TEXT_LOGGER_H_

#include <io/logger/ILogger.h>

namespace e2e {
namespace io {

class PlainTextLogger : public ILogger {
   public:
    PlainTextLogger(const std::string& pathToOutputFile);

    virtual void logInfo(const std::string& infoMessage) const override;

    virtual void logWarning(const std::string& warningMessage) const override;

    virtual void logError(const std::string& errorMessage) const override;

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

   private:
    const std::string pathToOutputFile;

    void writeOutputToFile(const std::string& output) const;
};

}  // namespace io
}  // namespace e2e

#endif