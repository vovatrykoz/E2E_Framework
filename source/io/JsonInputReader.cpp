#include "io/JsonInputReader.h"

#include <fstream>
#include <sstream>
#include <string>

JsonInputReader::JsonInputReader(const std::string& filePath)
    : filePath(filePath) {}

std::set<TimedPath> JsonInputReader::readPathsSet() const {
    std::ifstream file(this->filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Error: File not found");
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find("  ", pos)) != std::string::npos) {
            line.erase(pos, 2);
        }

        lines.push_back(line);
    }

    file.close();

    if (lines[0] != "[") {
        throw std::runtime_error("Error: File is not formatted correctly");
    }

    return parseTaskChain(lines);
}

std::set<TimedPath> JsonInputReader::parseTaskChain(
    const std::vector<std::string>& pathsSetStrings) const {
    if (pathsSetStrings[0] != "[") {
        throw std::runtime_error("Error: File is not formatted correctly");
    }
}