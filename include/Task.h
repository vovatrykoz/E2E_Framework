#ifndef _TASK_H_
#define _TASK_H_

namespace e2e {

/**
 * @struct PeriodicTask
 * @brief Represents a task with its execution parameters.
 *
 * A `PeriodicTask` is a core unit of scheduling. It contains information about the
 * task's period, worst-case response time (WCRT), priority, and an optional
 * offset.
 *
 * Tasks are used to describe periodic tasks in a real-time system, where each
 * task has a period (time between executions), a WCRT (maximum time it takes to
 * complete), a priority (used for scheduling), and an offset (delays the first
 * execution).
 */
struct PeriodicTask {
    int period;    // The period of the task (in time units).
    int wcrt;      // The worst-case response time (in time units).
    int priority;  // The priority of the task (higher value means higher
                   // priority).
    int offset =
        0;  // The offset (initial delay before task execution), default is 0.

    /**
     * @brief Constructs a PeriodicTask with a specified period, WCRT, and priority.
     * @param period The period of the task.
     * @param wcrt The worst-case response time of the task.
     * @param priority The priority of the task.
     */
    PeriodicTask(int period, int wcrt, int priority)
        : period(period), wcrt(wcrt), priority(priority) {}

    /**
     * @brief Constructs a PeriodicTask with a specified period, WCRT, priority, and
     * offset.
     * @param period The period of the task.
     * @param wcrt The worst-case response time of the task.
     * @param priority The priority of the task.
     * @param offset The offset (initial delay) for the task.
     */
    PeriodicTask(int period, int wcrt, int priority, int offset)
        : period(period), wcrt(wcrt), priority(priority), offset(offset) {}

    /**
     * @brief Equality operator for comparing two PeriodicTask objects.
     * @param other The task to compare with.
     * @return True if the tasks are equal, false otherwise.
     */
    bool operator==(const PeriodicTask& other) const;

    /**
     * @brief Inequality operator for comparing two PeriodicTask objects.
     * @param other The task to compare with.
     * @return True if the tasks are not equal, false otherwise.
     */
    bool operator!=(const PeriodicTask& other) const;
};

/**
 * @struct PeriodicTaskInstance
 * @brief Represents an instance of a task in time.
 *
 * A `PeriodicTaskInstance` extends a `PeriodicTask` by adding an activation time that specifies
 * when the task should be executed. Each `PeriodicTaskInstance` represents a specific
 * execution of a task, occurring at a specific point in time.
 */
struct PeriodicTaskInstance {
    PeriodicTask baseTask;  // The base task, which contains the task's period, WCRT,
                    // priority, and offset.
    int activationTime;  // The time at which this task instance is activated.

    /**
     * @brief Constructs a PeriodicTaskInstance with a base task and an activation time.
     * @param baseTask The base task object representing the task.
     * @param activationTime The activation time of this task instance.
     */
    PeriodicTaskInstance(const PeriodicTask& baseTask, int activationTime)
        : baseTask(baseTask), activationTime(activationTime) {}

    /**
     * @brief Gets the next instance of the task.
     *
     * The next task instance is calculated based on the period of the base task
     * and the current instance's activation time.
     *
     * @return The next `PeriodicTaskInstance` based on the current one.
     */
    PeriodicTaskInstance nextInstance() const;

    /**
     * @brief Equality operator for comparing two PeriodicTaskInstance objects.
     * @param other The task instance to compare with.
     * @return True if the task instances are equal, false otherwise.
     */
    bool operator==(const PeriodicTaskInstance& other) const;

    /**
     * @brief Inequality operator for comparing two PeriodicTaskInstance objects.
     * @param other The task instance to compare with.
     * @return True if the task instances are not equal, false otherwise.
     */
    bool operator!=(const PeriodicTaskInstance& other) const;
};

inline bool PeriodicTask::operator==(const PeriodicTask& other) const {
    return this->period == other.period && this->wcrt == other.wcrt &&
           this->priority == other.priority;
}

inline bool PeriodicTask::operator!=(const PeriodicTask& other) const {
    return !(*this == other);
}

inline bool PeriodicTaskInstance::operator==(const PeriodicTaskInstance& other) const {
    return this->baseTask == other.baseTask &&
           this->activationTime == other.activationTime;
}

inline bool PeriodicTaskInstance::operator!=(const PeriodicTaskInstance& other) const {
    return !(*this == other);
}

}  // namespace e2e

#endif