#ifndef _TASK_H_
#define _TASK_H_

struct Task {
    int period;
    int wcet;

    Task(int period, int wcet) : period(period), wcet(wcet) {}
};

struct TaskInstance {
    int activationTime;
    int wcet;

    TaskInstance(int activationTime, int wcet) : activationTime(activationTime), wcet(wcet) {}
};

#endif