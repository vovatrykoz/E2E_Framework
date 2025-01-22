#ifndef _PLAIN_TEXT_TASK_READER_H_
#define _PLAIN_TEXT_TASK_READER_H_

#include <io/reader/ITaskReader.h>

namespace e2e {
namespace io {

class PlainTextTaskReader : public ITaskReader {
public:
    PlainTextTaskReader(const std::string& filePath);

    virtual std::vector<NamedTask> readTaskChain() const override;

private:
    OffsetPeriodicTask parseTask(const std::string& taskStr) const;

    const std::string filePath;
    static const std::string startStr;
    static const std::string endStr;
};

}  // namespace io
}  // namespace e2e

#endif