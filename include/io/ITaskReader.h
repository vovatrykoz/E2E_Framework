#ifndef _I_TASK_READER_H_
#define _I_TASK_READER_H_

#include <Task.h>

#include <vector>

namespace e2e {
namespace io {

class ITaskReader {
public:
    virtual std::vector<Task> readTaskChain() const = 0;
    virtual ~ITaskReader() = default;
};

}  // namespace io
}  // namespace e2e

#endif