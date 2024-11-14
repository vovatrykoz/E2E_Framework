#ifndef _I_READER_H_
#define _I_READER_H_

#include <TimedPath.h>

#include <set>
#include <string>

class IReader {
public:
    virtual std::set<TimedPath> readPathsSet() const = 0;
    virtual ~IReader() = default;
};

#endif