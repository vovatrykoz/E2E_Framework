#include "SimpleTextTaskReader.h"

#include <fstream>
#include <sstream>

using namespace e2e;
using namespace e2e::io;

std::vector<NamedTask> SimpleTextTaskReader::readTaskChain() const {
    std::ifstream file(this->filePath);

    if (!file) {
        throw std::runtime_error("Error: file not found");
    }

    std::vector<NamedTask> output;
    std::vector<std::vector<std::string>> lines;

    bool isOnTask = false;
    std::string line;
    NamedTask namedTask(Task(0, 0, 0, 0), "");

    while (std::getline(file, line)) {
        size_t startStringPos = line.find(this->startStr);
        if (startStringPos != std::string::npos) {
            isOnTask = true;
            size_t namePos = startStringPos + 6;
            std::string name = line.substr(namePos);
            namedTask.name = name;
            continue;
        }

        if (line.find(this->endStr) != std::string::npos) {
            output.push_back(namedTask);
            isOnTask = false;
        }

        if (isOnTask) {
            Task task = this->parseTask(line);
            namedTask.task = task;
        }
    }

    return output;
}

Task SimpleTextTaskReader::parseTask(
    const std::string& taskStr) const {
    std::vector<std::string> taskParams;
    std::stringstream ss(taskStr);

    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        taskParams.push_back(substr);
    }

    if (taskParams.size() != 4) {
        throw std::runtime_error("Error: file is not formatted correctly");
    }

    try {
        int period = std::stoi(taskParams[0]);
        int wcrt = std::stoi(taskParams[1]);
        int priority = std::stoi(taskParams[2]);
        int offset = std::stoi(taskParams[3]);

        return Task(Task(period, wcrt, priority, offset));
    } catch (...) {
        throw std::runtime_error("Error: could not parse some of the lines");
    }
}
