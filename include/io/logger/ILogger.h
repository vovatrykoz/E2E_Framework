#ifndef _I_LOGGER_H_
#define _I_LOGGER_H_

#include <TimedPath.h>

#include <optional>
#include <set>

namespace e2e {
namespace io {

/**
 * @brief Interface for logging various timed path results.
 *
 * The ILogger interface defines methods for logging the results related to
 * timed paths, including valid/invalid paths, maximum latency, and path delays.
 * This interface is intended to be implemented by concrete logger classes that
 * handle different logging mechanisms (e.g., console logging, file logging).
 */
class ILogger {
   public:
    /**
     * @brief Logs the valid and invalid paths.
     *
     * This function logs the entire multiset of paths, along with separate logs
     * for valid and invalid paths. It helps in analyzing the correctness of the
     * paths.
     *
     * @param allPathsSet A multiset containing all the timed paths.
     * @param validPathSet A multiset containing valid timed paths.
     * @param invalidPathSet A multiset containing invalid timed paths.
     */
    virtual void logValidAndInvalidPaths(
        const std::multiset<TimedPath>& allPathsSet,
        const std::multiset<TimedPath>& validPathSet,
        const std::multiset<TimedPath>& invalidPathSet) const = 0;

    /**
     * @brief Logs the results of maximum latency path calculation (LL).
     *
     * This function logs the path with the maximum latency, where latency is
     * typically defined as the time delay from start to end of the path.
     *
     * @param maximumLatencyPath An optional TimedPath representing the path
     * with the maximum latency.
     */
    virtual void logResults_LL(
        const std::optional<TimedPath>& maximumLatencyPath) const = 0;

    /**
     * @brief Logs the results of latency from first to last task (LF).
     *
     * This function logs the maximum latency path from the first task to
     * the last task in the timed path.
     *
     * @param maximumLatencyPath An optional TimedPath representing the
     * path with the maximum latency.
     */
    virtual void logResults_LF(
        const std::optional<TimedPath>& maximumLatencyPath) const = 0;

    /**
     * @brief Logs the results of the maximum first-to-last path delay.
     *
     * This function logs the maximum delay between the first and last
     * task instances in a timed path.
     *
     * @param maxFirstToLastPathDelay The maximum first-to-last path delay.
     */
    virtual void logResults_FL(int maxFirstToLastPathDelay) const = 0;

    /**
     * @brief Logs the results of the maximum first-to-first path delay.
     *
     * This function logs the maximum delay between the first task instance
     * of the path and the first task instance of the next cycle.
     *
     * @param maxFirstToFirstPathDelay The maximum first-to-first path delay.
     */
    virtual void logResults_FF(int maxFirstToFirstPathDelay) const = 0;

    /**
     * @brief Virtual destructor for the logger.
     *
     * This virtual destructor ensures proper cleanup of any derived classes.
     */
    virtual ~ILogger() = default;
};

}  // namespace io
}  // namespace e2e

#endif