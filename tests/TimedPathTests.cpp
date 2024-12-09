#include <TimedPath.h>
#include <gtest/gtest.h>

using namespace e2e;

TEST(TimedPath, CanAppendTaskToPath) {
    PeriodicTask task(10, 5, 1);
    PeriodicTaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.appendTaskInstance(taskInstance);

    std::vector<PeriodicTaskInstance> expected = {taskInstance};
    std::vector<PeriodicTaskInstance> actual = tp.asVector();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, CanPopTaskFromPath) {
    PeriodicTask task(10, 5, 1);
    PeriodicTaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.appendTaskInstance(taskInstance);
    tp.popTaskInstance();

    std::vector<PeriodicTaskInstance> expected;
    std::vector<PeriodicTaskInstance> actual = tp.asVector();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, ReturnsZeroWhenCalculatingEndToEndDelayForEmptyTaskPath) {
    TimedPath tp;

    int expected = 0;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, ReturnsWcetWhenCalculatingEndToEndDelayForTaskPathWithOneTask) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTaskInstance t1Instance(t1, 4);

    TimedPath tp;
    tp.appendTaskInstance(t1Instance);

    int expected = t1.wcrt;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, CanCalculateEndToEndDelayForTaskPath) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    PeriodicTaskInstance t1Instance(t1, 4);
    PeriodicTaskInstance t2Instance(t2, 11);
    PeriodicTaskInstance t3Instance(t3, 15);
    PeriodicTaskInstance t4Instance(t4, 22);

    TimedPath tp;
    tp.appendTaskInstance(t1Instance);
    tp.appendTaskInstance(t2Instance);
    tp.appendTaskInstance(t3Instance);
    tp.appendTaskInstance(t4Instance);

    int expected = 19;
    int actual = tp.endToEndDelay();

    EXPECT_EQ(expected, actual);
}