// Contains functions from section 3.4 Mathematical Framework
// Some of the description text is copy-pasted from A Compositional Framework
// for End-to-End Path Delay Calculation of Automotive Systems under Different
// Path Semantics to make finding relevant functions easier

#ifndef _MATH_FRAMEWORK_H_
#define _MATH_FRAMEWORK_H_

#include <Task.h>

namespace MathFramework {

/**
 * @brief Checks if "activation time travel" occurs between two tasks.
 *
 * The following boolean function att returns true if “activation
 * time travel” occurs (i.e. when the reader is activated
 * before the writer), and false if it doesn’t
 *
 * @param writerTask The task instance representing the writer task.
 * @param readerTask The task instance representing the reader task.
 * @return true if activation time travel occurs (reader activates before
 * writer).
 * @return false if activation time travel does not occur.
 */
bool att(const TaskInstance& writerTaskInstance,
         const TaskInstance& readerTaskInstance);

/**
 * @brief Determines if the writer and reader tasks overlap in execution.
 *
 * The more important “critical function” crit determines if
 * (even in case of non-activation time travel) writer and reader
 * overlap in execution:
 *
 * @param writerTask The task instance representing the writer.
 * @param readerTask The task instance representing the reader.
 * @return true if there is an overlap in execution between writer and reader.
 * @return false if there is no overlap in execution.
 */
bool crit(const TaskInstance& writerTaskInstance,
          const TaskInstance& readerTaskInstance);

/**
 * @brief Determines if the reader task must wait due to the writer's priority.
 * 
 * The waiting function wait determines if (in case of
 * overlapped but not time-traveling execution) the writer finishes
 * first, because the reader has to wait due to its priority
 * 
 * @param writerTask The task representing the writer.
 * @param readerTask The task representing the reader.
 * @return true if the reader must wait for the writer to finish due to priority.
 * @return false if the reader does not need to wait for the writer.
 */
bool wait(const Task& writerTask, const Task& readerTask);

}

#endif