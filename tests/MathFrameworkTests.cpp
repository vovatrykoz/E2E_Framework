#include <MathFramework.h>
#include <gtest/gtest.h>

TEST(MathFramework, CanDetectTimeTravel) {
    const TaskInstance writerTask(10, 5);
    const TaskInstance readerTask(5, 5);

    bool expected = true;
    bool actual = att(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}

TEST(MathFramework, CanDetectWhenThereIsNoTimeTravel) {
    const TaskInstance writerTask(5, 5);
    const TaskInstance readerTask(10, 5);

    bool expected = false;
    bool actual = att(writerTask, readerTask);

    EXPECT_EQ(expected, actual);
}