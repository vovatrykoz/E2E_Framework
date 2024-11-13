#ifndef _TIMED_PATH_H_
#define _TIMED_PATH_H_

#include <Task.h>

#include <vector>

class TimedPath {
public:
    void appendTaskInstance(const TaskInstance& taskInstance);
    void popTaskInstance();
    int endToEndDelay() const;
    std::vector<TaskInstance> toVector() const;
    const std::vector<TaskInstance>& asVector() const;
private:
    std::vector<TaskInstance> tasks;
};

inline void TimedPath::appendTaskInstance(const TaskInstance& taskInstance) {
    this->tasks.push_back(taskInstance);
}

inline std::vector<TaskInstance> TimedPath::toVector() const {
    return this->tasks;
}

inline const std::vector<TaskInstance>& TimedPath::asVector() const {
    return this->tasks;
}

#endif