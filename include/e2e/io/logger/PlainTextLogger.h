#ifndef _PLAIN_TEXT_LOGGER_H_
#define _PLAIN_TEXT_LOGGER_H_

#include <e2e/io/logger/IResultLogger.h>

namespace e2e {
namespace io {

class PlainTextLogger : public IResultLogger {
   public:
    PlainTextLogger(const std::string& pathToOutputFile);

    virtual void logValidAndInvalidPaths(
        const std::vector<TimedPath>& allPathsSet,
        const std::vector<TimedPath>& validPathSet,
        const std::vector<TimedPath>& invalidPathSet) const override;

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