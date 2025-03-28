#ifndef _PLAIN_TEXT_TASK_INSTANCE_READER_H_
#define _PLAIN_TEXT_TASK_INSTANCE_READER_H_

#include <e2e/io/reader/ITaskInstanceReader.h>

namespace e2e {
namespace io {

class PlainTextTaskInstanceReader : public ITaskInstanceReader {
   public:
    PlainTextTaskInstanceReader(const std::string& filePath);

    virtual std::vector<TimedPath> readPathsSet() const override;

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