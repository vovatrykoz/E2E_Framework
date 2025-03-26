// Contains functions from section 3.4 Mathematical Framework
// Some of the description text is copy-pasted from A Compositional Framework
// for End-to-End Path Delay Calculation of Automotive Systems under Different
// Path Semantics to make finding relevant functions easier

#ifndef _MATH_FRAMEWORK_H_
#define _MATH_FRAMEWORK_H_

#include <PeriodicTask.h>

#include <vector>

namespace e2e {
namespace mathframework {

/**
 * @brief Checks if "activation time travel" occurs between two tasks.
 *
 * "The following boolean function att returns true if “activation
 * time travel” occurs (i.e. when the reader is activated
 * before the writer), and false if it doesn’t" Feiertag et al. page 5
 *
 * @param writerTask The task instance representing the writer task.
 * @param readerTask The task instance representing the reader task.
 * @return true if activation time travel occurs (reader activates before
 * writer).
 * @return false if activation time travel does not occur.
 */
[[gnu::pure]]
bool att(const PeriodicTaskInstance& writerTaskInstance,
         const PeriodicTaskInstance& readerTaskInstance);

/**
 * @brief Determines if the writer and reader tasks overlap in execution.
 *
 * "The more important “critical function” crit determines if
 * (even in case of non-activation time travel) writer and reader
 * overlap in execution" Feiertag et al. page 5
 *
 * @param writerTaskInstance The task instance representing the writer.
 * @param readerTaskInstance The task instance representing the reader.
 * @return true if there is an overlap in execution between writer and reader.
 * @return false if there is no overlap in execution.
 */
[[gnu::pure]]
bool crit(const PeriodicTaskInstance& writerTaskInstance,
          const PeriodicTaskInstance& readerTaskInstance);

/**
 * @brief Determines if the reader task must wait due to the writer's priority.
 *
 * "The waiting function wait determines if (in case of overlapped but not
 * time-traveling execution) the writer finishes first, because the reader has
 * to wait due to its priority" Feiertag et al. page 5
 *
 * @param writerTask The task representing the writer.
 * @param readerTask The task representing the reader.
 * @return true if the reader must wait for the writer to finish due to
 * priority.
 * @return false if the reader does not need to wait for the writer.
 */
[[gnu::pure]]
bool wait(const PeriodicTask& writerTask, const PeriodicTask& readerTask);

/**
 * @brief Determines the forward reachability between two task instances.
 *
 * "Now, we can combine these to define a boolean function
 * forw determining the forward reachability of the two
 * instances. The instances must not time travel (Eqn. 3)
 * and additionally be either not critical (Eqn. 4) or wait
 * (Eqn. 5)" Feiertag et al. page 5
 *
 * @param writerTaskInstance The task representing the writer.
 * @param readerTaskInstance The task representing the reader.
 * @return true if forward reachability conditions are met.
 * @return false if forward reachability conditions are not met.
 */
[[gnu::pure]]
bool forw(const PeriodicTaskInstance& writerTaskInstance,
          const PeriodicTaskInstance& readerTaskInstance);

/**
 * @brief Checks if a writer task instance can reach a reader task instance,
 * detecting potential overwrites.
 *
 * "From this forward reachability, we can also detect overwrites.
 * The output of an instance `tw(i)` is overwritten by
 * instance `tw(i + 1)` when both instances can forward reach
 * the same reading task instance `tr(j)`. In other words, `tw(i)`
 * can reach `tr(j)` if and only if the following function returns
 * true" Feiertag et al. page 5
 *
 * @param currentWriterTaskInstance The current writer task instance, `tw(i)`.
 * @param readerTaskInstance The reader task instance, `tr(j)`.
 * @param nextWriterTaskInstance The next writer task instance, `tw(i + 1)`.
 * @return true if the current writer task instance can reach the reader task
 * instance.
 * @return false if it cannot reach the reader task instance, indicating an
 * overwrite.
 */
[[gnu::pure]]
bool reach(const PeriodicTaskInstance& currentWriterTaskInstance,
           const PeriodicTaskInstance& readerTaskInstance,
           const PeriodicTaskInstance& nextWriterTaskInstance);

/**
 * @brief Determines reachability for an entire timed path of task instances.
 *
 * "From this reachability between two task instances, we
 * can now define the reachability function for a whole timed
 * path. A timed path is reachable, if and only if every two
 * consecutive task instances within that path are reachable." Feiertag et al.
 * page 5
 *
 * @param timedPath A vector of task instances representing the timed path.
 * @return true if the entire timed path is reachable.
 * @return false if any two consecutive task instances in the path are not
 * reachable.
 */
[[gnu::pure]]
bool pathReach(const std::vector<PeriodicTaskInstance>& timedPath);

}  // namespace mathframework
}  // namespace e2e

#endif