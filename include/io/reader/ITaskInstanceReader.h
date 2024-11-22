#ifndef _I_TASK_INSTANCE_READER_H_
#define _I_TASK_INSTANCE_READER_H_

#include <TimedPath.h>

#include <set>
#include <string>

namespace e2e {
namespace io {

/**
 * @brief Interface for reading task instance paths.
 *
 * The ITaskInstanceReader interface defines a method for reading a set of
 * timed paths, where each path represents a sequence of task instances
 * associated with specific timing information. This allows different 
 * implementations to read paths from various sources (e.g., files, databases).
 */
class ITaskInstanceReader {
public:
    /**
     * @brief Reads a set of timed paths.
     *
     * This method returns a set of `TimedPath` objects, where each `TimedPath`
     * contains a sequence of task instances. The set ensures that each path
     * is unique within the collection.
     *
     * @return A set of timed paths, where each path represents a valid sequence 
     *         of task instances.
     */
    virtual std::set<TimedPath> readPathsSet() const = 0;

    /**
     * @brief Virtual destructor for the task instance reader.
     *
     * This virtual destructor ensures proper cleanup of any derived classes.
     */
    virtual ~ITaskInstanceReader() = default;
};


}  // namespace io
}  // namespace e2e

#endif