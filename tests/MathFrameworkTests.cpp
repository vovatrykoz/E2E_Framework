#include <MathFramework.h>
#include <gtest/gtest.h>

TEST(MathFramework, CanDetectTimeTravel) {
    Task writerTask(10, 5);
    Task readerTask(5, 5);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 5);

    bool expected = true;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CanDetectWhenThereIsNoTimeTravel) {
    Task writerTask(10, 5);
    Task readerTask(5, 5);

    TaskInstance writerTaskInstance(writerTask, 5);
    TaskInstance readerTaskInstance(readerTask, 10);

    bool expected = false;
    bool actual = att(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectExecutionOverlap) {
    Task writerTask(10, 5);
    Task readerTask(5, 5);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 12);

    bool expected = true;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CritFunctionCanDetectWhenThereIsNoExecutionOverlap) {
    Task writerTask(10, 5);
    Task readerTask(5, 5);

    TaskInstance writerTaskInstance(writerTask, 10);
    TaskInstance readerTaskInstance(readerTask, 16);

    bool expected = false;
    bool actual = crit(writerTaskInstance, readerTaskInstance);

    EXPECT_EQ(expected, actual);
}