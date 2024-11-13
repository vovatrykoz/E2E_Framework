#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include <TimedPath.h>

#include <set>

namespace Analysis {

    std::set<TimedPath> removeUnreachablePaths(const std::set<TimedPath>& pathSet);

    int calculateMaximumLatency(const std::set<TimedPath>& pathSet);

}  // namespace analysis

#endif