#include <TaskScheduling.h>
#include <gtest/gtest.h>

using namespace e2e;

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

TEST(TaskScheduling, EmptyTaskChainReturnsEmptyTaskInstanceChain) {
    std::vector<std::vector<TaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath({});

    EXPECT_TRUE(actual.empty());
}

TEST(TaskScheduling,
     TaskChainReturnsWithOneTaskReturnsSingleTaskInstanceInChain) {
    Task t1(40, 4, 1);

    std::vector<std::vector<TaskInstance>> expected = {{TaskInstance(t1, 0)}};
    std::vector<std::vector<TaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath({t1});

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasks) {
    Task t1(20, 4, 1);
    Task t2(40, 3, 1);
    Task t3(4, 2, 1);

    std::vector<Task> tasks = {t1, t2, t3};

    std::vector<std::vector<TaskInstance>> expected = {
        {TaskInstance(t1, 0), TaskInstance(t1, 20)},
        {TaskInstance(t2, 0)},
        {TaskInstance(t3, 0), TaskInstance(t3, 4), TaskInstance(t3, 8),
         TaskInstance(t3, 12), TaskInstance(t3, 16), TaskInstance(t3, 20),
         TaskInstance(t3, 24), TaskInstance(t3, 28), TaskInstance(t3, 32),
         TaskInstance(t3, 36)}};

    std::vector<std::vector<TaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CorrectInstanceChainsForSeveralTasksWithOffsets) {
    Task t1(20, 4, 1, 2);
    Task t2(40, 3, 1, 7);
    Task t3(4, 2, 1, 5);

    std::vector<Task> tasks = {t1, t2, t3};

    std::vector<std::vector<TaskInstance>> expected = {
        {TaskInstance(t1, 2), TaskInstance(t1, 22)},
        {TaskInstance(t2, 7)},
        {TaskInstance(t3, 5), TaskInstance(t3, 9), TaskInstance(t3, 13),
         TaskInstance(t3, 17), TaskInstance(t3, 21), TaskInstance(t3, 25),
         TaskInstance(t3, 29), TaskInstance(t3, 33), TaskInstance(t3, 37),
         TaskInstance(t3, 41)}};

    std::vector<std::vector<TaskInstance>> actual =
        scheduling::generateTaskInstancesFromPath(tasks);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, EmptyTaskChainReturnsEmptySet) {
    std::set<TimedPath> actual = scheduling::generateTimedPathsFromInstances({});

    EXPECT_TRUE(actual.empty());
}

TEST(TaskScheduling, TaskChainWithOneInstanceChain) {
    Task t1(40, 4, 1);

    std::vector<std::vector<TaskInstance>> taskInstanceChain = {
        {TaskInstance(t1, 0)}};

    TimedPath onlyPossiblePath("#1", taskInstanceChain[0]);

    std::set<TimedPath> expected = {onlyPossiblePath};

    std::set<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(taskInstanceChain);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, TaskChainWithOneTaskReturnsSetWithPathContainingOneTask) {
    Task t1(20, 4, 1);

    std::vector<std::vector<TaskInstance>> taskInstanceChain = {
        {TaskInstance(t1, 0), TaskInstance(t1, 20), TaskInstance(t1, 40)}};

    TimedPath tp1("#1", {taskInstanceChain[0][0]});
    TimedPath tp2("#2", {taskInstanceChain[0][1]});
    TimedPath tp3("#3", {taskInstanceChain[0][2]});

    std::set<TimedPath> expected = {tp1, tp2, tp3};

    std::vector<std::vector<TaskInstance>> possiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstanceChain);

    std::set<TimedPath> actual = scheduling::generateTimedPathsFromInstances(possiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanBuildTaskChain) {
    Task t1(20, 4, 1);
    Task t2(40, 3, 1);
    Task t3(4, 2, 1);

    std::vector<Task> tasks = {t1, t2, t3};

    std::vector<std::vector<TaskInstance>> expected = {
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 0)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 4)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 8)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 12)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 16)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 20)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 24)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 28)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 32)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 36)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 0)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 4)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 8)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 12)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 16)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 20)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 24)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 28)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 32)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 36)}};

    std::vector<std::vector<TaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<TaskInstance>> actual =
        scheduling::buildTaskExecutionPaths(taskInstances);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSet) {
    Task t1(20, 4, 1);
    Task t2(40, 3, 1);
    Task t3(4, 2, 1);

    std::vector<Task> tasks = {t1, t2, t3};

    std::vector<std::vector<TaskInstance>> possiblePaths = {
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 0)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 4)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 8)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 12)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 16)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 20)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 24)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 28)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 32)},
        {TaskInstance(t1, 0), TaskInstance(t2, 0), TaskInstance(t3, 36)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 0)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 4)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 8)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 12)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 16)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 20)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 24)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 28)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 32)},
        {TaskInstance(t1, 20), TaskInstance(t2, 0), TaskInstance(t3, 36)}};

    std::set<TimedPath> expected;
    int counter = 1;
    for (const auto& path : possiblePaths) {
        std::string pathId = "#" + std::to_string(counter);
        expected.insert(TimedPath(pathId, path));
        counter++;
    }

    std::vector<std::vector<TaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<TaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::set<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual);
}

TEST(TaskScheduling, CanCreateTimedPathSetForMoreComplexTasks) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<Task> tasks = {t1, t2, t3, t4};

    std::size_t expected = 864;

    std::vector<std::vector<TaskInstance>> taskInstances =
        scheduling::generateTaskInstancesFromPath(tasks);

    std::vector<std::vector<TaskInstance>> actualPossiblePaths =
        scheduling::buildTaskExecutionPaths(taskInstances);

    std::set<TimedPath> actual =
        scheduling::generateTimedPathsFromInstances(actualPossiblePaths);

    EXPECT_EQ(expected, actual.size());
}