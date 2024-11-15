#include <Analysis.h>
#include <gtest/gtest.h>

using namespace analysis;

TEST(Analysis, CanRemoveUnreachablePaths) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<TaskInstance> unreachablePath_1 = {
        TaskInstance(t1, 0), TaskInstance(t2, 11), TaskInstance(t3, 5),
        TaskInstance(t4, 22)};

    std::vector<TaskInstance> unreachablePath_2 = {
        TaskInstance(t1, 0), TaskInstance(t2, 100), TaskInstance(t3, 15),
        TaskInstance(t4, 22)};

    std::vector<TaskInstance> unreachablePath_3 = {
        TaskInstance(t1, 40), TaskInstance(t2, 51), TaskInstance(t3, 75),
        TaskInstance(t4, 92)};

    std::vector<TaskInstance> reachablePath_1 = {
        TaskInstance(t1, 0), TaskInstance(t2, 11), TaskInstance(t3, 15),
        TaskInstance(t4, 32)};

    std::vector<TaskInstance> reachablePath_2 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 52)};

    std::vector<TaskInstance> reachablePath_3 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 72)};

    TimedPath timedPath_A("A", unreachablePath_1);
    TimedPath timedPath_B("B", unreachablePath_2);
    TimedPath timedPath_C("C", reachablePath_1);
    TimedPath timedPath_D("D", reachablePath_2);
    TimedPath timedPath_E("E", reachablePath_3);

    std::set<TimedPath> timedPaths = {timedPath_A, timedPath_B, timedPath_C,
                                      timedPath_D, timedPath_E};

    std::set<TimedPath> expected = {timedPath_C, timedPath_D, timedPath_E};

    std::set<TimedPath> actual = removeUnreachablePaths(timedPaths);

    EXPECT_EQ(expected, actual);
}

TEST(Analysis, CanCalculateLongestEndToEndTime) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<TaskInstance> reachablePath_1 = {
        TaskInstance(t1, 0), TaskInstance(t2, 11), TaskInstance(t3, 15),
        TaskInstance(t4, 32)};

    std::vector<TaskInstance> reachablePath_2 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 52)};

    std::vector<TaskInstance> reachablePath_3 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 72)};

    std::vector<TaskInstance> reachablePath_4 = {
        TaskInstance(t1, 40), TaskInstance(t2, 71), TaskInstance(t3, 75),
        TaskInstance(t4, 92)};

    TimedPath timedPath_A("A", reachablePath_1);
    TimedPath timedPath_B("B", reachablePath_2);
    TimedPath timedPath_C("C", reachablePath_3);
    TimedPath timedPath_D("D", reachablePath_4);

    std::set<TimedPath> timedPaths = {timedPath_A, timedPath_B, timedPath_C,
                                      timedPath_D};

    // 72 + 1 - 0
    int expectedLatency = 73;
    TimedPath expectedPath = timedPath_C;
    std::optional<TimedPath> actualValueContainer =
        getPathWithMaximumLatency(timedPaths);

    ASSERT_TRUE(actualValueContainer.has_value());

    TimedPath actualPath = actualValueContainer.value();
    int actualLatency = actualPath.endToEndDelay();

    EXPECT_EQ(expectedPath, actualPath);
}

TEST(Analysis, NoEndToEndTimeIfThereAreNoPaths) {
    std::set<TimedPath> timedPaths;
    std::optional<TimedPath> actualValueContainer =
        getPathWithMaximumLatency(timedPaths);

    ASSERT_FALSE(actualValueContainer.has_value());
}

TEST(Analysis, CanAnalyzeUsingLastToFirstSemantics) {
    Task t1(40, 4, 1);
    Task t2(10, 3, 1);
    Task t3(30, 2, 1);
    Task t4(20, 1, 1);

    std::vector<TaskInstance> unreachablePath_2 = {
        TaskInstance(t1, 0), TaskInstance(t2, 100), TaskInstance(t3, 15),
        TaskInstance(t4, 22)};

    std::vector<TaskInstance> unreachablePath_3 = {
        TaskInstance(t1, 40), TaskInstance(t2, 51), TaskInstance(t3, 75),
        TaskInstance(t4, 92)};

    std::vector<TaskInstance> reachablePath_1 = {
        TaskInstance(t1, 0), TaskInstance(t2, 11), TaskInstance(t3, 15),
        TaskInstance(t4, 32)};

    std::vector<TaskInstance> reachablePath_2 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 52)};

    std::vector<TaskInstance> reachablePath_3 = {
        TaskInstance(t1, 0), TaskInstance(t2, 41), TaskInstance(t3, 45),
        TaskInstance(t4, 72)};

    TimedPath timedPath_A("A", reachablePath_1);
    TimedPath timedPath_B("B", reachablePath_2);
    TimedPath timedPath_C("C", reachablePath_3);
    TimedPath timedPath_E("E", unreachablePath_2);
    TimedPath timedPath_F("F", unreachablePath_3);

    std::set<TimedPath> timedPaths = {timedPath_A, timedPath_B, timedPath_C,
                                      timedPath_E, timedPath_F};

    int expectedLatency = timedPath_A.endToEndDelay();
    TimedPath expectedPath = timedPath_A;

    std::set<TimedPath> reachablePaths = removeUnreachablePaths(timedPaths);
    std::set<TimedPath> reachablePaths_LF =
        removeDublicatesWithSameStart(reachablePaths);

    std::optional<TimedPath> actualValueContainer =
        getPathWithMaximumLatency(reachablePaths_LF);

    ASSERT_TRUE(actualValueContainer.has_value());

    TimedPath actualPath = actualValueContainer.value();
    int actualLatency = actualPath.endToEndDelay();

    EXPECT_EQ(actualLatency, expectedLatency);
    EXPECT_EQ(expectedPath, actualPath);
}

// the following tests are based on Figure 7. Example with Task Schedule and
// Several End-to-End Semantics from the paper by Feiertag et al.
TEST(Analysis, CanAnalyzeUsingFirstToLastSemantics) {
    Task t1(20, 5, 1);
    Task t2(40, 1, 1);
    Task t3(10, 1, 1);

    TaskInstance t1_firstInstance(t1, 0);
    TaskInstance t1_thirdInstance(
        t1, t1_firstInstance.activationTime + t1.period * 2);

    TaskInstance t2_firstInstance(t2, 5);
    TaskInstance t2_secondInstance(t2,
                                   t2_firstInstance.activationTime + t2.period);

    TaskInstance t3_fourthInstance(t3, 39);
    TaskInstance t3_eighthInstance(
        t3, t3_fourthInstance.activationTime + t3.period * 4);

    std::vector<TaskInstance> firstPath = {t1_firstInstance, t2_firstInstance,
                                           t3_fourthInstance};

    std::vector<TaskInstance> secondPath = {t1_thirdInstance, t2_secondInstance,
                                            t3_eighthInstance};

    TimedPath firstTimedPath("First path", firstPath);
    TimedPath secondTimedPath("Second path", secondPath);

    // = delta_LL(secondTimedPath) + a(t1_thirdInstance) - a(t1_firstInstance) =
    // 40 + 40 - 0 = 80
    int expectedFirstToLastDelay = 80;
    TimedPath expectedPath = secondTimedPath;

    std::set<TimedPath> paths = {firstTimedPath, secondTimedPath};

    // make sure both paths are reachable
    std::set<TimedPath> reachablePaths = removeUnreachablePaths(paths);

    int actualFirstToLastDelay = analysis::getFirstToLastPathDelay(reachablePaths);

    EXPECT_EQ(expectedFirstToLastDelay, actualFirstToLastDelay);
}