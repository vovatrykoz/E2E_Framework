#ifndef _TASK_H_
#define _TASK_H_

struct Task {
    int period;
    int wcrt;
    int priority;
    int offset = 0;

    Task(int period, int wcrt, int priority)
        : period(period), wcrt(wcrt), priority(priority) {}

    Task(int period, int wcrt, int priority, int offset)
        : period(period), wcrt(wcrt), priority(priority), offset(offset) {}

    bool operator==(const Task& other) const;
    bool operator!=(const Task& other) const;
};

struct TaskInstance {
    Task baseTask;
    int activationTime;

    TaskInstance(const Task& baseTask, int activationTime)
        : baseTask(baseTask), activationTime(activationTime) {}

    TaskInstance nextInstance() const;

    bool operator==(const TaskInstance& other) const;
    bool operator!=(const TaskInstance& other) const;
};

inline bool Task::operator==(const Task& other) const {
    return this->period == other.period && this->wcrt == other.wcrt &&
           this->priority == other.priority;
}

inline bool Task::operator!=(const Task& other) const {
    return !(*this == other);
}

inline bool TaskInstance::operator==(const TaskInstance& other) const {
    return this->baseTask == other.baseTask &&
           this->activationTime == other.activationTime;
}

inline bool TaskInstance::operator!=(const TaskInstance& other) const {
    return !(*this == other);
}

#endif