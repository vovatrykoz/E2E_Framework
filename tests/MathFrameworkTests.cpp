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