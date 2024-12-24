#include "io/reader/PlainTextTaskInstanceReader.h"

#include <fstream>
#include <sstream>

using namespace e2e;
using namespace e2e::io;

PlainTextTaskInstanceReader::PlainTextTaskInstanceReader(
    const std::string& filePath)
    : filePath(filePath) {}

std::multiset<TimedPath> PlainTextTaskInstanceReader::readPathsSet() const {
    std::ifstream file(this->filePath);

    if (!file) {
        throw std::runtime_error("Error: file not found");
    }

    std::multiset<TimedPath> output;
    std::vector<std::vector<std::string>> lines;

    bool isOnTaskChain = false;
    std::string line;
    TimedPath path;

    while (std::getline(file, line)) {
        size_t startStringPos = line.find(this->startStr);
        if (startStringPos != std::string::npos) {
            isOnTaskChain = true;
            size_t namePos = startStringPos + 6;
            std::string name = line.substr(namePos);
            path = TimedPath(name);
            continue;
        }

        if (line.find(this->endStr) != std::string::npos) {
            output.insert(path);
            isOnTaskChain = false;
        }

        if (isOnTaskChain) {
            PeriodicTaskInstance taskInstance = this->parseTaskInstance(line);
            path.appendTaskInstance(taskInstance);
        }
    }

    return output;
}

PeriodicTaskInstance PlainTextTaskInstanceReader::parseTaskInstance(
    const std::string& taskInstanceStr) const {
    std::vector<std::string> taskInstanceParams;
    std::stringstream ss(taskInstanceStr);

    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        taskInstanceParams.push_back(substr);
    }

    if (taskInstanceParams.size() != 4) {
        throw std::runtime_error("Error: file is not formatted correctly");
    }

    try {
        int period = std::stoi(taskInstanceParams[0]);
        int wcrt = std::stoi(taskInstanceParams[1]);
        int priority = std::stoi(taskInstanceParams[2]);
        int activaionTime = std::stoi(taskInstanceParams[3]);

        return PeriodicTaskInstance(PeriodicTask(period, wcrt, priority),
                                    activaionTime);
    } catch (...) {
        throw std::runtime_error("Error: could not parse some of the lines");
    }
}

const std::string PlainTextTaskInstanceReader::startStr = "START";
const std::string PlainTextTaskInstanceReader::endStr = "END";