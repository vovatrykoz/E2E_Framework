#ifndef _I_TASK_READER_H_
#define _I_TASK_READER_H_

#include <Task.h>

#include <string>
#include <vector>

namespace e2e {
namespace io {

struct NamedTask;

class ITaskReader {
public:
    virtual std::vector<NamedTask> readTaskChain() const = 0;
    virtual ~ITaskReader() = default;
};

struct NamedTask {
    Task task;
    std::string name;
};

}  // namespace io
}  // namespace e2e

#endif