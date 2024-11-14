#ifndef _CONSOLE_LOGGER_H_
#define _CONSOLE_LOGGER_H_

#include <TimedPath.h>

#include <set>

class ConsoleLogger {
public:
    void logResults(const std::set<TimedPath>& allPathsSet,
                    const std::set<TimedPath>& validPathSet,
                    const std::set<TimedPath>& invalidPathSet,
                    int maximumLatency);
};

#endif