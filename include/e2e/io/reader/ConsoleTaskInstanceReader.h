#ifndef _CONSOLE_INSTANCE_READER_H_
#define _CONSOLE_INSTANCE_READER_H_

#include <e2e/io/reader/ITaskInstanceReader.h>

#include <set>
#include <string>

namespace e2e {
namespace io {

class ConsoleTaskInstanceReader : public ITaskInstanceReader {
   public:
    virtual std::vector<TimedPath> readPathsSet() const override;

   private:
    int readInt(const std::string& message) const;
    PeriodicTaskInstance readTaskInstance() const;
    TimedPath readTimedPath(const std::string& name) const;
};

}  // namespace io
}  // namespace e2e

#endif