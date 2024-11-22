#ifndef _SIMPLE_TEXT_TASK_READER_H_
#define _SIMPLE_TEXT_TASK_READER_H_

#include <io/reader/ITaskReader.h>

namespace e2e {
namespace io {

class SimpleTextTaskReader : public ITaskReader {
public:
    SimpleTextTaskReader(const std::string& filePath);

    virtual std::vector<NamedTask> readTaskChain() const override;

private:
    Task parseTask(const std::string& taskStr) const;

    const std::string filePath;
    static const std::string startStr;
    static const std::string endStr;
};

}  // namespace io
}  // namespace e2e

#endif