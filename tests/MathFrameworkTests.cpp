#include <MathFramework.h>
#include <gtest/gtest.h>

using namespace MathFramework;

TEST(MathFramework, CanDetectTimeTravel) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 5);

    bool expected = true;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CanDetectWhenThereIsNoTimeTravel) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 5);
    TaskInstance readerTaskInstance(readerTask, 10);

    bool expected = false;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectExecutionOverlap) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);

    bool expected = true;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectWhenThereIsNoExecutionOverlap) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 16);

    bool expected = false;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, WaitFunctionCanDetectReaderWaiting) {
    Task writerTask(10, 5, 2);
    Task readerTask(5, 5, 1);

    bool expected = true;
    bool actual = wait(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, WaitFunctionCanDetectWhenReaderDoesNotHaveToWait) {
    Task writerTask(10, 5, 2);
    Task readerTask(5, 5, 2);

    bool expected = false;
    bool actual = wait(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}

TEST(
    MathFramework,
    ForwCanDetectForwardReachabilityWhenThereIsNoTimeTravelAndTasksAreNonCritical) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 2);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 16);

    bool expected = true;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(
    MathFramework,
    ForwCanDetectForwardReachabilityWhenThereIsNoTimeTravelAndReaderHasToWait) {
    Task writerTask(10, 5, 2);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);

    bool expected = true;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework,
     ForwCanDetectWhenThereIsNoForwardReachabilityDueToTimeTravel) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 5);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework,
     ForwCanDetectWhenThereIsNoForwardReachabilityDueToCriticality) {
    Task writerTask(10, 5, 1);
    Task readerTask(5, 5, 2);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ForwCanDetectWhenThereIsNoForwardReachabilityDueToNoWait) {
    Task writerTask(10, 5, 2);
    Task readerTask(5, 5, 2);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ReachCanDetectOverwrites) {
    Task writerTask(10, 5, 1);
    Task readerTask(20, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);
    TaskInstance nextWriterTaskInstance(
        writerTask, writerTaskInstance.activationTime + writerTask.period);

    bool expected = false;
    bool actual =
        reach(writerTaskInstance, readerTaskInstance, nextWriterTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ReachCanDetectNoOverwrites) {
    Task writerTask(10, 5, 1);
    Task readerTask(10, 5, 1);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 16);
    TaskInstance nextWriterTaskInstance(
        writerTask, writerTaskInstance.activationTime + writerTask.period);

    bool expected = true;
    bool actual =
        reach(writerTaskInstance, readerTaskInstance, nextWriterTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachReturnsFalseIfPathIsEmpty) {
    std::vector<TaskInstancePair> timedPath;

    bool expected = false;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachReturnsFalseIfPathOnlyHasOneTask) {
    Task task(10, 5, 1);
    TaskInstance currentTaskInstance(task, 10);
    TaskInstance nextTaskInstance(task, currentTaskInstance.activationTime + currentTaskInstance.baseTask.period);

    TaskInstancePair taskPair(currentTaskInstance, nextTaskInstance);

    std::vector<TaskInstancePair> timedPath;
    timedPath.push_back(taskPair);

    bool expected = true;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachKnowsWhenTaskChainIsReachable) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    TaskInstance t1Instance(t1, 0);
    TaskInstance t2Instance(t2, 11);
    TaskInstance t3Instance(t3, 15);
    TaskInstance t4Instance(t4, 22);

    TaskInstance t1NextInstance(t1, t1Instance.activationTime + t1.period);
    TaskInstance t2NextInstance(t2, t2Instance.activationTime + t2.period);
    TaskInstance t3NextInstance(t3, t3Instance.activationTime + t3.period);
    TaskInstance t4NextInstance(t4, t4Instance.activationTime + t4.period);

    TaskInstancePair t1Pair(t1Instance, t1NextInstance);
    TaskInstancePair t2Pair(t2Instance, t2NextInstance);
    TaskInstancePair t3Pair(t3Instance, t3NextInstance);
    TaskInstancePair t4Pair(t4Instance, t4NextInstance);

    std::vector<TaskInstancePair> timedPath;
    timedPath.push_back(t1Pair);
    timedPath.push_back(t2Pair);
    timedPath.push_back(t3Pair);
    timedPath.push_back(t4Pair);

    bool expected = true;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachKnowsWhenTaskChainIsUnreachable) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    TaskInstance t1Instance(t1, 0);
    TaskInstance t2Instance(t2, 11);
    TaskInstance t3Instance(t3, 5);
    TaskInstance t4Instance(t4, 22);

    TaskInstance t1NextInstance(t1, t1Instance.activationTime + t1.period);
    TaskInstance t2NextInstance(t2, t2Instance.activationTime + t2.period);
    TaskInstance t3NextInstance(t3, t3Instance.activationTime + t3.period);
    TaskInstance t4NextInstance(t4, t4Instance.activationTime + t4.period);

    TaskInstancePair t1Pair(t1Instance, t1NextInstance);
    TaskInstancePair t2Pair(t2Instance, t2NextInstance);
    TaskInstancePair t3Pair(t3Instance, t3NextInstance);
    TaskInstancePair t4Pair(t4Instance, t4NextInstance);

    std::vector<TaskInstancePair> timedPath;
    timedPath.push_back(t1Pair);
    timedPath.push_back(t2Pair);
    timedPath.push_back(t3Pair);
    timedPath.push_back(t4Pair);

    bool expected = false;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}