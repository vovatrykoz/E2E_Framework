#ifndef _TASK_H_
#define _TASK_H_

struct Task {
    int period;
    int wcet;

    Task(int period, int wcet) : period(period), wcet(wcet) {}
};

struct TaskInstance {
    Task baseTask;
    int activationTime;

    TaskInstance(const Task& baseTask, int activationTime)
        : baseTask(baseTask), activationTime(activationTime) {}
};

#endif