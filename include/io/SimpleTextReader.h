#ifndef _SIMPLE_TEXT_READER_H_
#define _SIMPLE_TEXT_READER_H_

#include <io/IReader.h>

namespace e2e {
namespace io {

class SimpleTextReader : public IReader {
public:
    SimpleTextReader(const std::string& filePath);

    virtual std::set<TimedPath> readPathsSet() const override;

private:
    TaskInstance parseTaskInstance(const std::string& taskInstanceStr) const;

    const std::string filePath;
    static const std::string startStr;
    static const std::string endStr;
};

}  // namespace io
}  // namespace e2e

#endif