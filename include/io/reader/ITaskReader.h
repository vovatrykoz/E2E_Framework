#ifndef _I_TASK_READER_H_
#define _I_TASK_READER_H_

#include <PeriodicTask.h>

#include <string>
#include <vector>

namespace e2e {
namespace io {

struct NamedTask;

/**
 * @brief Interface for reading a chain of named tasks.
 *
 * The ITaskReader interface defines a method for reading a sequence (chain)
 * of tasks where each task is associated with a name. This interface allows
 * the implementation of different task reading mechanisms (e.g., reading from a
 * file, database, or another source).
 */
class ITaskReader {
public:
    /**
     * @brief Reads a chain of named tasks.
     *
     * This method returns a vector of `NamedTask` objects, where each
     * `NamedTask` consists of a `PeriodicTask` and its corresponding name. It
     * represents a sequence of tasks to be executed in a certain order.
     *
     * @return A vector containing the named tasks in the chain.
     */
    virtual std::vector<NamedTask> readTaskChain() const = 0;

    /**
     * @brief Virtual destructor for the task reader.
     *
     * This virtual destructor ensures proper cleanup of any derived classes.
     */
    virtual ~ITaskReader() = default;
};

/**
 * @brief A struct representing a task with an associated name.
 *
 * The `NamedTask` struct combines a `PeriodicTask` object with a name. The name
 * helps in identifying or labeling the task, which could be useful for logging,
 * debugging, or task management.
 */
struct NamedTask {
    OffsetPeriodicTask task;  // The task object that contains task-specific data like
                        // period, latency, etc.
    std::string name;  // The name associated with the task.

    /**
     * @brief Constructs a NamedTask object.
     *
     * Initializes a NamedTask with a specific task and its associated name.
     *
     * @param task The PeriodicTask object representing the task's properties.
     * @param name The name associated with the task.
     */
    NamedTask(OffsetPeriodicTask task, const std::string& name)
        : task(task), name(name) {}
};

}  // namespace io
}  // namespace e2e

#endif