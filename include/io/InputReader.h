#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_

#include <io/IReader.h>

#include <set>
#include <string>

class InputReader : public IReader {
public:
    virtual std::set<TimedPath> readPathsSet() const override;

private:
    int readInt(const std::string& message) const;
    TaskInstance readTaskInstance() const;
    TimedPath readTimedPath(const std::string& name) const;
};

#endif