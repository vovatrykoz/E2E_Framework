#ifndef _MATH_FRAMEWORK_H_
#define _MATH_FRAMEWORK_H_

#include <Task.h>

// Contains functions from section 3.4 Mathematical Framework

/**
 * The following boolean function att returns true if “activation
 * time travel” occurs (i.e. when the reader is activated
 * before the writer), and false if it doesn’t
 */
bool att(const TaskInstance& writerTask, const TaskInstance& readerTask);

#endif