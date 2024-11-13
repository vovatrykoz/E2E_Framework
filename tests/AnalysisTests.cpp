#include <Analysis.h>
#include <gtest/gtest.h>

using namespace analysis;

TEST(analysis, CanRemoveUnreachablePaths) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<TaskInstance> unreachablePath_1 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 11),
        TaskInstance(t3, 5),
        TaskInstance(t4, 22)
    };

    std::vector<TaskInstance> unreachablePath_2 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 100),
        TaskInstance(t3, 15),
        TaskInstance(t4, 22)
    };

    std::vector<TaskInstance> unreachablePath_3 = {
        TaskInstance(t1, 40),
        TaskInstance(t2, 51),
        TaskInstance(t3, 75),
        TaskInstance(t4, 92)
    };

    std::vector<TaskInstance> reachablePath_1 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 11),
        TaskInstance(t3, 15),
        TaskInstance(t4, 32)
    };

    std::vector<TaskInstance> reachablePath_2 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 41),
        TaskInstance(t3, 45),
        TaskInstance(t4, 52)
    };

    std::vector<TaskInstance> reachablePath_3 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 41),
        TaskInstance(t3, 45),
        TaskInstance(t4, 72)
    };


    TimedPath timedPath_A("A", unreachablePath_1);
    TimedPath timedPath_B("B", unreachablePath_2);
    TimedPath timedPath_C("C", reachablePath_1);
    TimedPath timedPath_D("D", reachablePath_2);
    TimedPath timedPath_E("E", reachablePath_3);

    std::set<TimedPath> timedPaths = {
        timedPath_A,
        timedPath_B,
        timedPath_C,
        timedPath_D,
        timedPath_E
    };

    std::set<TimedPath> expected = {
        timedPath_C,
        timedPath_D,
        timedPath_E
    };

    std::set<TimedPath> actual = removeUnreachablePaths(timedPaths);

    EXPECT_EQ(expected, actual);
}

TEST(analysis, CanCalculateLongestEndToEndTime) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<TaskInstance> reachablePath_1 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 11),
        TaskInstance(t3, 15),
        TaskInstance(t4, 32)
    };

    std::vector<TaskInstance> reachablePath_2 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 41),
        TaskInstance(t3, 45),
        TaskInstance(t4, 52)
    };

    std::vector<TaskInstance> reachablePath_3 = {
        TaskInstance(t1, 0),
        TaskInstance(t2, 41),
        TaskInstance(t3, 45),
        TaskInstance(t4, 72)
    };

    std::vector<TaskInstance> reachablePath_4 = {
        TaskInstance(t1, 40),
        TaskInstance(t2, 71),
        TaskInstance(t3, 75),
        TaskInstance(t4, 92)
    };

    TimedPath timedPath_A("A", reachablePath_1);
    TimedPath timedPath_B("B", reachablePath_2);
    TimedPath timedPath_C("C", reachablePath_3);
    TimedPath timedPath_D("D", reachablePath_4);

    std::set<TimedPath> timedPaths = {
        timedPath_A,
        timedPath_B,
        timedPath_C,
        timedPath_D
    };

    // 72 + 1 - 0
    int expected = 73;
    int actual = calculateMaximumLatency(timedPaths);

    EXPECT_EQ(expected, actual);
}