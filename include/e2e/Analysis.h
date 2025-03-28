#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include <e2e/TimedPath.h>

#include <optional>
#include <vector>

namespace e2e {
namespace analysis {

/**
 * @brief Remove all unreachable paths from a multiset
 *
 * Removes all unreachable paths from the provided multiset. Each path in the
 * multiset is checked against the reachability conditions defined in
 * MathFramework.h and MathFramework.cpp. If the path passes all the checks, it
 * is added to the output multiset.
 *
 * @param pathSet A multiset of TimedPath objects to be checked for
 * reachability.
 *
 * @return A new multiset of TimedPath objects that are reachable according to
 * the reachability conditions.
 */
std::vector<TimedPath> removeUnreachablePaths(
    const std::vector<TimedPath>& pathSet);

/**
 * @brief Remove all paths that produce duplicate values
 *
 * Removes all paths that produce duplicate values due to identical start times.
 * This is relevant when using Last-To-First or Last-To-Last semantics.
 *
 * @param pathSet A multiset of TimedPath objects to be checked for duplicate
 * output.
 *
 * @return A new multiset of TimedPath objects that do not produce duplicate
 * values.
 */
std::vector<TimedPath> removePathsProducingDuplicateValues(
    const std::vector<TimedPath>& pathSet);

/**
 * @brief Finds the path with maximum end-to-end latency in the set
 *
 * Finds the path with maximum end-to-end latency in the set. Can be used to
 * perform end-to-end analysis using Last-to-Last or Last-to-First semantics
 *
 * @param pathSet A set of TimedPath objects to analyse
 *
 * @return A TimedPath with the maximum end-to-end latency, is such exists
 */
std::optional<TimedPath> getPathWithMaximumLatency(
    const std::vector<TimedPath>& pathSet);

/**
 * @brief Calculate path delay using First-to-x semantics
 *
 * Calculates path delay using either First-to-First or First-to-Last semantics.
 * The set that is passed into the function should be properly filtererd for
 * the analysis to be correct.
 *
 * @param pathSet A set of TimedPath objects to analyse
 *
 * @return Maximum path delay with First-to-x semantics
 */
int getOverarchingDelay(const std::vector<TimedPath>& pathSet);

/**
 * @brief Determines if a path has a "predecessor"
 *
 * A predecessor is a path that has an activation time of current path - path
 * period
 *
 * @param path A path for which we want to find a predecessor
 * @param pathSet A set of TimedPath objects to analyse
 *
 * @return Predecessor to path, if such exists
 */
std::optional<TimedPath> findPredecessor(const TimedPath& path,
                                         const std::vector<TimedPath>& pathSet);

}  // namespace analysis
}  // namespace e2e

#endif