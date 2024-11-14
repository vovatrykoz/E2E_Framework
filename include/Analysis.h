#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include <TimedPath.h>

#include <optional>
#include <set>

namespace analysis {

std::set<TimedPath> removeUnreachablePaths(const std::set<TimedPath>& pathSet);

std::set<TimedPath> removeDublicatesWithSameStart(
    const std::set<TimedPath>& pathSet);

std::optional<TimedPath> getPathWithMaximumLatency(
    const std::set<TimedPath>& pathSet);

}  // namespace analysis

#endif