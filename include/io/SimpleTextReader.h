#ifndef _SIMPLE_TEXT_READER_H_
#define _SIMPLE_TEXT_READER_H_

#include <TimedPath.h>
#include <string>
#include <set>

class SimpleTextReader {
public:
    SimpleTextReader(const std::string& filePath);

    std::set<TimedPath> readPathsSet() const;
private:
    TaskInstance parseTaskInstance(const std::string& taskInstanceStr) const;

    const std::string filePath;
    static const std::string startStr;
    static const std::string endStr;
};

#endif