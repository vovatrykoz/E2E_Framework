#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_

#include <TimedPath.h>

#include <set>
#include <string>
#include <iostream>

class InputReader {
public:
    std::set<TimedPath> readPathsSet() const;

private:
    int readInt(const std::string& message) const;
    TaskInstance readTaskInstance() const;
    TimedPath readTimedPath(const std::string& name) const;
};

#endif