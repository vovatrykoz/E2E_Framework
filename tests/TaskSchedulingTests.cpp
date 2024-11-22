#include <TaskScheduling.h>
#include <gtest/gtest.h>

TEST(TaskScheduling, EmptyTaskChainReturnsZero) {
    int expected = 0;
    int actual = scheduling::calculateLcmForEndToEndPath({});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, TaskChainReturnsWithOneTaskReturnsThatTasksPeriod) {
    Task t1(40, 4, 1);

    int expected = t1.period;
    int actual = scheduling::calculateLcmForEndToEndPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectLcmForSeveralTasks) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<Task> tasks = {t1, t2, t3, t4};

    int expected = 120;
    int actual = scheduling::calculateLcmForEndToEndPath(tasks);

    EXPECT_EQ(expected, actual);
}