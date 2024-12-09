#include <MathFramework.h>
#include <gtest/gtest.h>

using namespace e2e;
using namespace e2e::mathframework;

TEST(MathFramework, CanDetectTimeTravel) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 5);

    bool expected = true;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CanDetectWhenThereIsNoTimeTravel) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 5);
    PeriodicTaskInstance readerTaskInstance(readerTask, 10);

    bool expected = false;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectExecutionOverlap) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 12);

    bool expected = true;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectWhenThereIsNoExecutionOverlap) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 16);

    bool expected = false;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, WaitFunctionCanDetectReaderWaiting) {
    PeriodicTask writerTask(10, 5, 2);
    PeriodicTask readerTask(5, 5, 1);

    bool expected = true;
    bool actual = wait(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, WaitFunctionCanDetectWhenReaderDoesNotHaveToWait) {
    PeriodicTask writerTask(10, 5, 2);
    PeriodicTask readerTask(5, 5, 2);

    bool expected = false;
    bool actual = wait(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}

TEST(
    MathFramework,
    ForwCanDetectForwardReachabilityWhenThereIsNoTimeTravelAndTasksAreNonCritical) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 2);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 16);

    bool expected = true;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(
    MathFramework,
    ForwCanDetectForwardReachabilityWhenThereIsNoTimeTravelAndReaderHasToWait) {
    PeriodicTask writerTask(10, 5, 2);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 12);

    bool expected = true;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework,
     ForwCanDetectWhenThereIsNoForwardReachabilityDueToTimeTravel) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 5);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework,
     ForwCanDetectWhenThereIsNoForwardReachabilityDueToCriticality) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(5, 5, 2);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 12);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ForwCanDetectWhenThereIsNoForwardReachabilityDueToNoWait) {
    PeriodicTask writerTask(10, 5, 2);
    PeriodicTask readerTask(5, 5, 2);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 12);

    bool expected = false;
    bool actual = forw(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ReachCanDetectOverwrites) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(20, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 12);
    PeriodicTaskInstance nextWriterTaskInstance(
        writerTask, writerTaskInstance.activationTime + writerTask.period);

    bool expected = false;
    bool actual =
        reach(writerTaskInstance, readerTaskInstance, nextWriterTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, ReachCanDetectNoOverwrites) {
    PeriodicTask writerTask(10, 5, 1);
    PeriodicTask readerTask(10, 5, 1);

    PeriodicTaskInstance writerTaskInstance(writerTask, 10);
    PeriodicTaskInstance readerTaskInstance(readerTask, 16);
    PeriodicTaskInstance nextWriterTaskInstance(
        writerTask, writerTaskInstance.activationTime + writerTask.period);

    bool expected = true;
    bool actual =
        reach(writerTaskInstance, readerTaskInstance, nextWriterTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachReturnsFalseIfPathIsEmpty) {
    std::vector<PeriodicTaskInstance> timedPath;

    bool expected = false;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachReturnsFalseIfPathOnlyHasOneTask) {
    PeriodicTask task(10, 5, 1);
    PeriodicTaskInstance taskInstance(task, 10);

    std::vector<PeriodicTaskInstance> timedPath;
    timedPath.push_back(taskInstance);

    bool expected = true;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachKnowsWhenTaskChainIsReachable) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    PeriodicTaskInstance t1Instance(t1, 0);
    PeriodicTaskInstance t2Instance(t2, 11);
    PeriodicTaskInstance t3Instance(t3, 15);
    PeriodicTaskInstance t4Instance(t4, 22);

    std::vector<PeriodicTaskInstance> timedPath;
    timedPath.push_back(t1Instance);
    timedPath.push_back(t2Instance);
    timedPath.push_back(t3Instance);
    timedPath.push_back(t4Instance);

    bool expected = true;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, PathReachKnowsWhenTaskChainIsUnreachable) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    PeriodicTaskInstance t1Instance(t1, 0);
    PeriodicTaskInstance t2Instance(t2, 11);
    PeriodicTaskInstance t3Instance(t3, 5);
    PeriodicTaskInstance t4Instance(t4, 22);

    std::vector<PeriodicTaskInstance> timedPath;
    timedPath.push_back(t1Instance);
    timedPath.push_back(t2Instance);
    timedPath.push_back(t3Instance);
    timedPath.push_back(t4Instance);

    bool expected = false;
    bool actual = pathReach(timedPath);

    EXPECT_EQ(expected, actual);
}