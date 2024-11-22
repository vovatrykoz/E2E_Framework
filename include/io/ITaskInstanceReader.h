#ifndef _I_TASK_INSTANCE_READER_H_
#define _I_TASK_INSTANCE_READER_H_

#include <TimedPath.h>

#include <set>
#include <string>

namespace e2e {
namespace io {

class ITaskInstanceReader {
public:
    virtual std::set<TimedPath> readPathsSet() const = 0;
    virtual ~ITaskInstanceReader() = default;
};

}  // namespace io
}  // namespace e2e

#endif