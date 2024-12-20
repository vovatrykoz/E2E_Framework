#ifndef _TASK_INSTANCE_INPUT_READER_H_
#define _TASK_INSTANCE_INPUT_READER_H_

#include <io/reader/ITaskInstanceReader.h>

#include <set>
#include <string>

namespace e2e {
namespace io {

class TaskInstanceInputReader : public ITaskInstanceReader {
public:
    virtual std::multiset<TimedPath> readPathsSet() const override;

private:
    int readInt(const std::string& message) const;
    PeriodicTaskInstance readTaskInstance() const;
    TimedPath readTimedPath(const std::string& name) const;
};

}  // namespace io
}  // namespace e2e

#endif