#ifndef _MATH_FRAMEWORK_H_
#define _MATH_FRAMEWORK_H_

#include <Task.h>

// Contains functions from section 3.4 Mathematical Framework

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

#endif