// Contains functions from section 3.4 Mathematical Framework
// Some of the description text is copy-pasted from A Compositional Framework for End-to-End Path Delay Calculation
// of Automotive Systems under Different Path Semantics to make finding relevant functions easier

#ifndef _MATH_FRAMEWORK_H_
#define _MATH_FRAMEWORK_H_

#include <Task.h>

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
bool att(const TaskInstance& writerTask, const TaskInstance& readerTask);

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
bool crit(const TaskInstance& writerTask, const TaskInstance& readerTask);

#endif