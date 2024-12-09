#ifndef _TASK_INSTANCE_SIMPLE_TEXT_READER_H_
#define _TASK_INSTANCE_SIMPLE_TEXT_READER_H_

#include <io/reader/ITaskInstanceReader.h>

namespace e2e {
namespace io {

class TaskInstanceSimpleTextReader : public ITaskInstanceReader {
public:
    TaskInstanceSimpleTextReader(const std::string& filePath);

    virtual std::multiset<TimedPath> readPathsSet() const override;

private:
    PeriodicTaskInstance parseTaskInstance(
        const std::string& taskInstanceStr) const;

    const std::string filePath;
    static const std::string startStr;
    static const std::string endStr;
};

}  // namespace io
}  // namespace e2e

#endif