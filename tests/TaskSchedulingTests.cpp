#include <TaskScheduling.h>
#include <gtest/gtest.h>

using namespace e2e;

TEST(TaskScheduling, EmptyTaskChainReturnsZero) {
    int expected = 0;
    int actual = scheduling::calculateLcmForEndToEndPath({});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, TaskChainReturnsWithOneTaskReturnsThatTasksPeriod) {
    PeriodicTask t1(40, 4, 1);

    int expected = t1.period;
    int actual = scheduling::calculateLcmForEndToEndPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectLcmForSeveralTasks) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    std::vector<PeriodicTask> tasks = {t1, t2, t3, t4};

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
    PeriodicTask t1(40, 4, 1);

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1, 0)}};
    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasks) {
    PeriodicTask t1(20, 4, 1);
    PeriodicTask t2(40, 3, 1);
    PeriodicTask t3(4, 2, 1);

    std::vector<PeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t1, 20)},
        {PeriodicTaskInstance(t2, 0)},
        {PeriodicTaskInstance(t3, 0), PeriodicTaskInstance(t3, 4),
         PeriodicTaskInstance(t3, 8), PeriodicTaskInstance(t3, 12),
         PeriodicTaskInstance(t3, 16), PeriodicTaskInstance(t3, 20),
         PeriodicTaskInstance(t3, 24), PeriodicTaskInstance(t3, 28),
         PeriodicTaskInstance(t3, 32), PeriodicTaskInstance(t3, 36)}};

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasksWithOffsets) {
    PeriodicTask t1(20, 4, 1, 2);
    PeriodicTask t2(40, 3, 1, 7);
    PeriodicTask t3(4, 2, 1, 5);

    std::vector<PeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1, 2), PeriodicTaskInstance(t1, 22)},
        {PeriodicTaskInstance(t2, 7)},
        {PeriodicTaskInstance(t3, 5), PeriodicTaskInstance(t3, 9),
         PeriodicTaskInstance(t3, 13), PeriodicTaskInstance(t3, 17),
         PeriodicTaskInstance(t3, 21), PeriodicTaskInstance(t3, 25),
         PeriodicTaskInstance(t3, 29), PeriodicTaskInstance(t3, 33),
         PeriodicTaskInstance(t3, 37), PeriodicTaskInstance(t3, 41)}};

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, EmptyTaskChainReturnsEmptySet) {
    std::multiset<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances({});

    EXPECT_TRUE(actual.empty());
}

TEST(TaskScheduling, TaskChainWithOneInstanceChain) {
    PeriodicTask t1(40, 4, 1);

    std::vector<std::vector<PeriodicTaskInstance>> taskInstanceChain = {
        {PeriodicTaskInstance(t1, 0)}};

    TimedPath onlyPossiblePath("#1", taskInstanceChain[0]);

    std::multiset<TimedPath> expected = {onlyPossiblePath};

    std::multiset<TimedPath> actual =
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

    std::multiset<TimedPath> expected = {tp1, tp2, tp3};

    std::vector<std::vector<PeriodicTaskInstance>> possiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstanceChain);

    std::multiset<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(possiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanBuildTaskChain) {
    PeriodicTask t1(20, 4, 1);
    PeriodicTask t2(40, 3, 1);
    PeriodicTask t3(4, 2, 1);

    std::vector<PeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> expected = {
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 0)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 4)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 8)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 12)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 16)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 20)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 24)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 28)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 32)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 36)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 0)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 4)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 8)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 12)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 16)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 20)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 24)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 28)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 32)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 36)}};

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actual =
        scheduling::buildTaskExecutionPaths(taskInstances);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSet) {
    PeriodicTask t1(20, 4, 1);
    PeriodicTask t2(40, 3, 1);
    PeriodicTask t3(4, 2, 1);

    std::vector<PeriodicTask> tasks = {t1, t2, t3};

    std::vector<std::vector<PeriodicTaskInstance>> possiblePaths = {
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 0)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 4)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 8)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 12)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 16)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 20)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 24)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 28)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 32)},
        {PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 36)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 0)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 4)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 8)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 12)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 16)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 20)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 24)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 28)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 32)},
        {PeriodicTaskInstance(t1, 20), PeriodicTaskInstance(t2, 0),
         PeriodicTaskInstance(t3, 36)}};

    std::multiset<TimedPath> expected;
    int counter = 1;
    for (const auto& path : possiblePaths) {
        std::string pathId = "#" + std::to_string(counter);
        expected.insert(TimedPath(pathId, path));
        counter++;
    }

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::multiset<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSetForMoreComplexTasks) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    std::vector<PeriodicTask> tasks = {t1, t2, t3, t4};

    std::size_t expected = 864;

    std::vector<std::vector<PeriodicTaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<PeriodicTaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::multiset<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual.size());
}