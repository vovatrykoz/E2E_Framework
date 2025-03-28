#ifndef _TIMED_PATH_H_
#define _TIMED_PATH_H_

#include <e2e/PeriodicTask.h>

#include <string>
#include <vector>

namespace e2e {

/**
 * @brief Represents a timed path consisting of a sequence of task instances.
 *
 * The TimedPath class manages a series of PeriodicTaskInstance objects,
 * providing methods to add and remove instances, calculate the end-to-end
 * delay, and retrieve the sequence in different forms.
 */
class TimedPath {
   public:
    /**
     * @brief Default constructor for TimedPath.
     *
     * This constructor initializes an empty TimedPath. The `name` will be an
     * empty string, and the `tasks` vector will be empty. This constructor can
     * be used when a TimedPath is created without immediate task data or name.
     */
    TimedPath();

    /**
     * @brief Constructor for TimedPath with a name.
     *
     * This constructor initializes a TimedPath with a given name. The `tasks`
     * vector will be empty initially. This constructor is useful when you want
     * to create a TimedPath with a specific name but no tasks yet.
     *
     * @param name The name to assign to the TimedPath.
     */
    TimedPath(const std::string& name);

    /**
     * @brief Constructor for TimedPath with a list of task instances.
     *
     * This constructor initializes a TimedPath with a given sequence of task
     * instances. The `name` will be an empty string. This constructor is used
     * when the TimedPath is created with a set of tasks, but no name is needed.
     *
     * @param tasks A vector of PeriodicTaskInstance objects that will define
     * the sequence of tasks in the TimedPath.
     */
    TimedPath(const std::vector<PeriodicTaskInstance>& tasks);

    /**
     * @brief Constructor for TimedPath with a name and a list of task
     * instances.
     *
     * This constructor initializes a TimedPath with both a specific name and a
     * sequence of task instances. This is the most complete constructor, used
     * when both the name and the tasks for the TimedPath are known at the time
     * of creation.
     *
     * @param name  The name to assign to the TimedPath.
     * @param tasks A vector of PeriodicTaskInstance objects that will define
     * the sequence of tasks in the TimedPath.
     */
    TimedPath(const std::string& name,
              const std::vector<PeriodicTaskInstance>& tasks);

    /**
     * @brief The name of the timed path.
     *
     * This string property stores the name associated with the timed path.
     * It is used to identify and differentiate between various timed paths.
     * The name can be set when constructing the TimedPath object or modified
     * later.
     *
     * @note The name is optional, and if not explicitly set, it will default to
     * an empty string.
     */
    std::string name = "";

    /**
     * @brief Appends a task instance to the end of the timed path.
     *
     * @param taskInstance The PeriodicTaskInstance to add to the path.
     */
    void appendTaskInstance(const PeriodicTaskInstance& taskInstance);

    /**
     * @brief Removes the last task instance from the timed path. Popping from
     * an empty TimedPath is a harmless no-op
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
     * @brief Provides a const reference to the task instances in the timed
     * path.
     *
     * Returns a reference to the underlying vector of PeriodicTaskInstance
     * objects, allowing read-only access to the sequence.
     *
     * @return A const reference to the vector of task instances.
     */
    const std::vector<PeriodicTaskInstance>& asVector() const;

    /**
     * @brief Returns the activation time of the first task in the timed path.
     *
     * This function calculates the activation time of the first task in the
     * path by returning the activation time of the first task instance.
     *
     * @return The activation time of the first task in the timed path.
     */
    int firstTaskActivationTime() const;

    /**
     * @brief Returns the activation time of the last task in the timed path.
     *
     * This function calculates the activation time of the last task in the path
     * by returning the activation time of the last task instance.
     *
     * @return The activation time of the last task in the timed path.
     */
    int lastTaskActivationTime() const;

    /**
     * @brief Checks if the current timed path succeeds the given timed path.
     *
     * This function checks if the current timed path starts after the other
     * timed path finishes, making the current path a successor in terms of
     * activation time.
     *
     * @param other The other TimedPath to compare with.
     * @return true if the current path succeeds the other path, false
     * otherwise.
     */
    bool succeeds(const TimedPath& other) const;

    /**
     * @brief Calculates the period of the timed path.
     *
     * This function computes the period of the timed path, which is the time it
     * takes for the path to repeat its execution. It’s calculated as the
     * difference between the activation times of the first and last tasks in
     * the path.
     *
     * @return The period of the timed path.
     */
    int calculatePathPeriod() const;

    /**
     * @brief Compare two TimedPath objects by name
     *
     * Compares two TimedPath objects by name. Mainly needed so that we can
     * store TimedPath objects in ordered sets
     *
     * @return true if TimedPath on the lhs should come before the TimedPath on
     * the rhs
     */
    bool operator<(const TimedPath& other) const;

    /**
     * @brief Compare two TimedPath objects by name
     *
     * Compares two TimedPath objects by name. Mainly needed so that we can
     * store TimedPath objects in ordered sets
     *
     * @return true if the two TimedPaths have the same name, false otherwise
     */
    bool operator==(const TimedPath& other) const;

    /**
     * @brief Compare two TimedPath objects for inequality.
     *
     * This function checks if two TimedPath objects are not equal by comparing
     * their names.
     *
     * @param other The TimedPath object to compare with.
     * @return true if the TimedPath objects have different names, false
     * otherwise.
     */
    bool operator!=(const TimedPath& other) const;

   private:
    /**
     * Stores the sequence of task instances in the path.
     */
    std::vector<PeriodicTaskInstance> tasks =
        std::vector<PeriodicTaskInstance>();
};

inline TimedPath::TimedPath() {}

inline TimedPath::TimedPath(const std::string& name) : name(name) {}

inline TimedPath::TimedPath(const std::vector<PeriodicTaskInstance>& tasks)
    : tasks(tasks) {}

inline TimedPath::TimedPath(const std::string& name,
                            const std::vector<PeriodicTaskInstance>& tasks)
    : name(name), tasks(tasks) {}

inline void TimedPath::appendTaskInstance(
    const PeriodicTaskInstance& taskInstance) {
    this->tasks.push_back(taskInstance);
}

inline const std::vector<PeriodicTaskInstance>& TimedPath::asVector() const {
    return this->tasks;
}

inline bool TimedPath::operator<(const TimedPath& other) const {
    return this->name < other.name;
}

inline bool TimedPath::operator==(const TimedPath& other) const {
    return this->name == other.name;
}

inline bool TimedPath::operator!=(const TimedPath& other) const {
    return !(*this == other);
}

}  // namespace e2e

#endif