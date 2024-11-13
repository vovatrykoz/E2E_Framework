#ifndef _TASK_H_
#define _TASK_H_

struct Task {
    int period;
    int wcet;
    int priority;

    Task(int period, int wcet, int priority)
        : period(period), wcet(wcet), priority(priority) {}
};

struct TaskInstance {
    Task baseTask;
    int activationTime;

    TaskInstance(const Task& baseTask, int activationTime)
        : baseTask(baseTask), activationTime(activationTime) {}
};

#endif