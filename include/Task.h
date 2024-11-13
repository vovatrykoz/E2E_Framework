#ifndef _TASK_H_
#define _TASK_H_

struct Task {
    int period;
    int wcet;
    int priority;

    Task(int period, int wcet, int priority)
        : period(period), wcet(wcet), priority(priority) {}

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
    return this->period == other.period && this->wcet == other.wcet &&
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