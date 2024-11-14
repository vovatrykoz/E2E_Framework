#ifndef _JSON_INPUT_READER_H_
#define _JSON_INPUT_READER_H_

#include <TimedPath.h>

#include <iostream>
#include <set>
#include <string>

class JsonInputReader {
public:
    JsonInputReader(const std::string& filePath);

    std::set<TimedPath> readPathsSet() const;

private:
    const std::string filePath;

    std::set<TimedPath> parseTaskChain(
        const std::vector<std::string>& pathsSetString) const;
};

#endif