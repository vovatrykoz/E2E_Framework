#include <TimedPath.h>
#include <gtest/gtest.h>

TEST(TimedPath, CanAppendTaskToPath) {
    Task task(10, 5, 1);
    TaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.appendTaskInstance(taskInstance);

    std::vector<TaskInstance> expected = { taskInstance };
    std::vector<TaskInstance> actual = tp.toVector();

    EXPECT_EQ(expected, actual);
}

TEST(TimedPath, CanPopTaskFromPath) {
    Task task(10, 5, 1);
    TaskInstance taskInstance(task, 10);

    TimedPath tp;
    tp.popTaskInstance();

    std::vector<TaskInstance> expected;
    std::vector<TaskInstance> actual = tp.toVector();

    EXPECT_EQ(expected, actual);
}