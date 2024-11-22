#ifndef _CONSOLE_TASK_READER_H_
#define _CONSOLE_TASK_READER_H_

#include <io/ITaskReader.h>

namespace e2e {
namespace io {

class ConsoleTaskReader : public ITaskReader {
public:
    virtual std::vector<NamedTask> readTaskChain() const override;

private:
    int readInt(const std::string& message) const;
    NamedTask readTask() const;
};

}  // namespace io
}  // namespace e2e

#endif