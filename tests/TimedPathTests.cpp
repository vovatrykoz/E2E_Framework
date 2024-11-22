#include <TimedPath.h>
#include <gtest/gtest.h>

using namespace e2e;

TEST(TimedPath, CanAppendTaskToPath) {
    Task task(10, 5, 1);
    TaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.appendTaskInstance(taskInstance);

    std::vector<TaskInstance> expected = {taskInstance};
    std::vector<TaskInstance> actual = tp.asVector();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, CanPopTaskFromPath) {
    Task task(10, 5, 1);
    TaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.appendTaskInstance(taskInstance);
    tp.popTaskInstance();

    std::vector<TaskInstance> expected;
    std::vector<TaskInstance> actual = tp.asVector();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, ReturnsZeroWhenCalculatingEndToEndDelayForEmptyTaskPath) {
    TimedPath tp;

    int expected = 0;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, ReturnsWcetWhenCalculatingEndToEndDelayForTaskPathWithOneTask) {
    Task t1(40, 4, 1);
    TaskInstance t1Instance(t1, 4);

    TimedPath tp;
    tp.appendTaskInstance(t1Instance);

    int expected = t1.wcrt;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, CanCalculateEndToEndDelayForTaskPath) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    TaskInstance t1Instance(t1, 4);
    TaskInstance t2Instance(t2, 11);
    TaskInstance t3Instance(t3, 15);
    TaskInstance t4Instance(t4, 22);

    TimedPath tp;
    tp.appendTaskInstance(t1Instance);
    tp.appendTaskInstance(t2Instance);
    tp.appendTaskInstance(t3Instance);
    tp.appendTaskInstance(t4Instance);

    int expected = 19;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}