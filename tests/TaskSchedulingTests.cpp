#include <e2e/TaskScheduling.h>
#include <gtest/gtest.h>

using namespace e2e;

TEST(TaskScheduling, EmptyTaskChainReturnsZero) {
    int expected = 0;
    int actual = scheduling::calculateLcmForEndToEndPath({});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, TaskChainReturnsWithOneTaskReturnsThatTasksPeriod) {
    OffsetPeriodicTask t1(40, 4, 1);

    int expected = t1.baseTask.period;
    int actual = scheduling::calculateLcmForEndToEndPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectLcmForSeveralTasks) {
    OffsetPeriodicTask t1(40, 4, 1);
    OffsetPeriodicTask t2(10, 3, 1);
    OffsetPeriodicTask t3(30, 2, 1);
    OffsetPeriodicTask t4(20, 1, 1);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3, t4};

    int expected = 120;
    int actual = scheduling::calculateLcmForEndToEndPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, EmptyTaskChainReturnsEmptyTaskInstanceChain) {
    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath({});

    EXPECT_TRUE(actual.empty());
}

TEST(TaskScheduling,
     TaskChainReturnsWithOneTaskReturnsSingleTaskInstanceInChain) {
    OffsetPeriodicTask t1(40, 4, 1);
    PeriodicTaskInstance expectedTask = PeriodicTaskInstance{t1.baseTask, 0};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {{expectedTask}};
    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasks) {
    OffsetPeriodicTask t1(20, 4, 1);
    OffsetPeriodicTask t2(40, 3, 1);
    OffsetPeriodicTask t3(4, 2, 1);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t1.baseTask, 20)},
        {PeriodicTaskInstance(t2.baseTask, 0)},
        {PeriodicTaskInstance(t3.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 4),
         PeriodicTaskInstance(t3.baseTask, 8),
         PeriodicTaskInstance(t3.baseTask, 12),
         PeriodicTaskInstance(t3.baseTask, 16),
         PeriodicTaskInstance(t3.baseTask, 20),
         PeriodicTaskInstance(t3.baseTask, 24),
         PeriodicTaskInstance(t3.baseTask, 28),
         PeriodicTaskInstance(t3.baseTask, 32),
         PeriodicTaskInstance(t3.baseTask, 36)}};

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasksWithOffsets) {
    OffsetPeriodicTask t1(20, 4, 1, 2);
    OffsetPeriodicTask t2(40, 3, 1, 7);
    OffsetPeriodicTask t3(4, 2, 1, 5);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1.baseTask, 2),
         PeriodicTaskInstance(t1.baseTask, 22)},
        {PeriodicTaskInstance(t2.baseTask, 7)},
        {PeriodicTaskInstance(t3.baseTask, 5),
         PeriodicTaskInstance(t3.baseTask, 9),
         PeriodicTaskInstance(t3.baseTask, 13),
         PeriodicTaskInstance(t3.baseTask, 17),
         PeriodicTaskInstance(t3.baseTask, 21),
         PeriodicTaskInstance(t3.baseTask, 25),
         PeriodicTaskInstance(t3.baseTask, 29),
         PeriodicTaskInstance(t3.baseTask, 33),
         PeriodicTaskInstance(t3.baseTask, 37),
         PeriodicTaskInstance(t3.baseTask, 41)}};

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, EmptyTaskChainReturnsEmptySet) {
    std::vector<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances({});

    EXPECT_TRUE(actual.empty());
}

TEST(TaskScheduling, TaskChainWithOneInstanceChain) {
    PeriodicTask t1(40, 4, 1);

    std::vector<std::vector<PeriodicTaskInstance>> taskInstanceChain = {
        {PeriodicTaskInstance(t1, 0)}};

    TimedPath onlyPossiblePath("#1", taskInstanceChain[0]);

    std::vector<TimedPath> expected = {onlyPossiblePath};

    std::vector<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(taskInstanceChain);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, TaskChainWithOneTaskReturnsSetWithPathContainingOneTask) {
    PeriodicTask t1(20, 4, 1);

    std::vector<std::vector<PeriodicTaskInstance>> taskInstanceChain = {
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t1, 20),
         PeriodicTaskInstance(t1, 40)}};

    TimedPath tp1("#1", {taskInstanceChain[0][0]});
    TimedPath tp2("#2", {taskInstanceChain[0][1]});
    TimedPath tp3("#3", {taskInstanceChain[0][2]});

    std::vector<TimedPath> expected = {tp1, tp2, tp3};

    std::vector<std::vector<PeriodicTaskInstance>> possiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstanceChain);

    std::vector<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(possiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanBuildTaskChain) {
    OffsetPeriodicTask t1(20, 4, 1);
    OffsetPeriodicTask t2(40, 3, 1);
    OffsetPeriodicTask t3(4, 2, 1);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 0)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 4)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 8)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 12)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 16)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 20)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 24)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 28)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 32)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 36)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 0)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 4)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 8)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 12)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 16)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 20)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 24)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 28)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 32)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 36)}};

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::buildTaskExecutionPaths(taskInstances);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSet) {
    OffsetPeriodicTask t1(20, 4, 1);
    OffsetPeriodicTask t2(40, 3, 1);
    OffsetPeriodicTask t3(4, 2, 1);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> possiblePaths = {
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 0)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 4)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 8)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 12)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 16)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 20)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 24)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 28)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 32)},
        {PeriodicTaskInstance(t1.baseTask, 0),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 36)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 0)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 4)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 8)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 12)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 16)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 20)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 24)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 28)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 32)},
        {PeriodicTaskInstance(t1.baseTask, 20),
         PeriodicTaskInstance(t2.baseTask, 0),
         PeriodicTaskInstance(t3.baseTask, 36)}};

    std::vector<TimedPath> expected;
    int counter = 1;
    for (const auto& path : possiblePaths) {
        std::string pathId = "#" + std::to_string(counter);
        expected.push_back(TimedPath(pathId, path));
        counter++;
    }

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::vector<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSetForMoreComplexTasks) {
    OffsetPeriodicTask t1(40, 4, 1);
    OffsetPeriodicTask t2(10, 3, 1);
    OffsetPeriodicTask t3(30, 2, 1);
    OffsetPeriodicTask t4(20, 1, 1);

    std::vector<OffsetPeriodicTask> tasks = {t1, t2, t3, t4};

    std::size_t expected = 864;

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::vector<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual.size());
}