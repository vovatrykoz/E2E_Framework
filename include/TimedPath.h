#ifndef _TIMED_PATH_H_
#define _TIMED_PATH_H_

#include <Task.h>

#include <vector>

/**
 * @brief Represents a timed path consisting of a sequence of task instances.
 * 
 * The TimedPath class manages a series of TaskInstance objects, providing methods 
 * to add and remove instances, calculate the end-to-end delay, and retrieve the 
 * sequence in different forms.
 */
class TimedPath {
public:
    /**
     * @brief Appends a task instance to the end of the timed path.
     * 
     * @param taskInstance The TaskInstance to add to the path.
     */
    void appendTaskInstance(const TaskInstance& taskInstance);

    /**
     * @brief Removes the last task instance from the timed path.
     */
    void popTaskInstance();

    /**
     * @brief Calculates the end-to-end delay of the timed path.
     * 
     * Computes the total delay from the start of the first task instance to the 
     * end of the last one in the path.
     * 
     * @return The calculated end-to-end delay.
     */
    int endToEndDelay() const;

    /**
     * @brief Provides a const reference to the task instances in the timed path.
     * 
     * Returns a reference to the underlying vector of TaskInstance objects, 
     * allowing read-only access to the sequence.
     * 
     * @return A const reference to the vector of task instances.
     */
    const std::vector<TaskInstance>& asVector() const;

private:
    std::vector<TaskInstance> tasks; ///< Stores the sequence of task instances in the path.
};

inline void TimedPath::appendTaskInstance(const TaskInstance& taskInstance) {
    this->tasks.push_back(taskInstance);
}

inline const std::vector<TaskInstance>& TimedPath::asVector() const {
    return this->tasks;
}

#endif