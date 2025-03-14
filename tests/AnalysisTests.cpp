#include <Analysis.h>
#include <gtest/gtest.h>

using namespace e2e;
using namespace e2e::analysis;

TEST(Analysis, CanRemoveUnreachablePaths) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    std::vector<PeriodicTaskInstance> unreachablePath_1 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 11),
        PeriodicTaskInstance(t3, 5), PeriodicTaskInstance(t4, 22)};

    std::vector<PeriodicTaskInstance> unreachablePath_2 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 100),
        PeriodicTaskInstance(t3, 15), PeriodicTaskInstance(t4, 22)};

    std::vector<PeriodicTaskInstance> unreachablePath_3 = {
        PeriodicTaskInstance(t1, 40), PeriodicTaskInstance(t2, 51),
        PeriodicTaskInstance(t3, 75), PeriodicTaskInstance(t4, 92)};

    std::vector<PeriodicTaskInstance> reachablePath_1 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 11),
        PeriodicTaskInstance(t3, 15), PeriodicTaskInstance(t4, 32)};

    std::vector<PeriodicTaskInstance> reachablePath_2 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 52)};

    std::vector<PeriodicTaskInstance> reachablePath_3 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 72)};

    TimedPath timedPath_A("A", unreachablePath_1);
    TimedPath timedPath_B("B", unreachablePath_2);
    TimedPath timedPath_C("C", reachablePath_1);
    TimedPath timedPath_D("D", reachablePath_2);
    TimedPath timedPath_E("E", reachablePath_3);

    std::multiset<TimedPath> timedPaths = {
        timedPath_A, timedPath_B, timedPath_C, timedPath_D, timedPath_E};

    std::multiset<TimedPath> expected = {timedPath_C, timedPath_D, timedPath_E};

    std::multiset<TimedPath> actual = removeUnreachablePaths(timedPaths);

    EXPECT_EQ(expected, actual);
}

TEST(Analysis, CanCalculateLongestEndToEndTime) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    std::vector<PeriodicTaskInstance> reachablePath_1 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 11),
        PeriodicTaskInstance(t3, 15), PeriodicTaskInstance(t4, 32)};

    std::vector<PeriodicTaskInstance> reachablePath_2 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 52)};

    std::vector<PeriodicTaskInstance> reachablePath_3 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 72)};

    std::vector<PeriodicTaskInstance> reachablePath_4 = {
        PeriodicTaskInstance(t1, 40), PeriodicTaskInstance(t2, 71),
        PeriodicTaskInstance(t3, 75), PeriodicTaskInstance(t4, 92)};

    TimedPath timedPath_A("A", reachablePath_1);
    TimedPath timedPath_B("B", reachablePath_2);
    TimedPath timedPath_C("C", reachablePath_3);
    TimedPath timedPath_D("D", reachablePath_4);

    std::multiset<TimedPath> timedPaths = {timedPath_A, timedPath_B,
                                           timedPath_C, timedPath_D};

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
    std::multiset<TimedPath> timedPaths;
    std::optional<TimedPath> actualValueContainer =
        getPathWithMaximumLatency(timedPaths);

    ASSERT_FALSE(actualValueContainer.has_value());
}

TEST(Analysis, CanAnalyzeUsingLastToFirstSemantics) {
    PeriodicTask t1(40, 4, 1);
    PeriodicTask t2(10, 3, 1);
    PeriodicTask t3(30, 2, 1);
    PeriodicTask t4(20, 1, 1);

    std::vector<PeriodicTaskInstance> unreachablePath_2 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 100),
        PeriodicTaskInstance(t3, 15), PeriodicTaskInstance(t4, 22)};

    std::vector<PeriodicTaskInstance> unreachablePath_3 = {
        PeriodicTaskInstance(t1, 40), PeriodicTaskInstance(t2, 51),
        PeriodicTaskInstance(t3, 75), PeriodicTaskInstance(t4, 92)};

    std::vector<PeriodicTaskInstance> reachablePath_1 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 11),
        PeriodicTaskInstance(t3, 15), PeriodicTaskInstance(t4, 32)};

    std::vector<PeriodicTaskInstance> reachablePath_2 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 52)};

    std::vector<PeriodicTaskInstance> reachablePath_3 = {
        PeriodicTaskInstance(t1, 0), PeriodicTaskInstance(t2, 41),
        PeriodicTaskInstance(t3, 45), PeriodicTaskInstance(t4, 72)};

    TimedPath timedPath_A("A", reachablePath_1);
    TimedPath timedPath_B("B", reachablePath_2);
    TimedPath timedPath_C("C", reachablePath_3);
    TimedPath timedPath_E("E", unreachablePath_2);
    TimedPath timedPath_F("F", unreachablePath_3);

    std::multiset<TimedPath> timedPaths = {
        timedPath_A, timedPath_B, timedPath_C, timedPath_E, timedPath_F};

    int expectedLatency = timedPath_A.endToEndDelay();
    TimedPath expectedPath = timedPath_A;

    std::multiset<TimedPath> reachablePaths =
        removeUnreachablePaths(timedPaths);
    std::multiset<TimedPath> reachablePaths_LF =
        removePathsProducingDuplicateValues(reachablePaths);

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
    PeriodicTask t1(20, 5, 1);
    PeriodicTask t2(40, 1, 1);
    PeriodicTask t3(10, 1, 1);

    PeriodicTaskInstance t1_firstInstance(t1, 0);
    PeriodicTaskInstance t1_thirdInstance(
        t1, t1_firstInstance.activationTime + t1.period * 2);

    PeriodicTaskInstance t2_firstInstance(t2, 5);
    PeriodicTaskInstance t2_secondInstance(
        t2, t2_firstInstance.activationTime + t2.period);

    PeriodicTaskInstance t3_fourthInstance(t3, 39);
    PeriodicTaskInstance t3_eighthInstance(
        t3, t3_fourthInstance.activationTime + t3.period * 4);

    std::vector<PeriodicTaskInstance> firstPath = {
        t1_firstInstance, t2_firstInstance, t3_fourthInstance};

    std::vector<PeriodicTaskInstance> secondPath = {
        t1_thirdInstance, t2_secondInstance, t3_eighthInstance};

    TimedPath firstTimedPath("First path", firstPath);
    TimedPath secondTimedPath("Second path", secondPath);

    // = delta_LL(secondTimedPath) + a(t1_thirdInstance) - a(t1_firstInstance) =
    // 40 + 40 - 0 = 80
    int expectedFirstToLastDelay = 80;
    TimedPath expectedPath = secondTimedPath;

    std::multiset<TimedPath> paths = {firstTimedPath, secondTimedPath};

    // make sure both paths are reachable
    std::multiset<TimedPath> reachablePaths = removeUnreachablePaths(paths);

    int actualFirstToLastDelay = analysis::getOverarchingDelay(reachablePaths);

    EXPECT_EQ(expectedFirstToLastDelay, actualFirstToLastDelay);
}

TEST(Analysis, CanAnalyzeUsingFirstToFirstSemantics) {
    PeriodicTask t1(20, 5, 1);
    PeriodicTask t2(40, 1, 1);
    PeriodicTask t3(10, 1, 1);

    PeriodicTaskInstance t1_firstInstance(t1, 0);
    PeriodicTaskInstance t1_thirdInstance(
        t1, t1_firstInstance.activationTime + t1.period * 2);

    PeriodicTaskInstance t2_firstInstance(t2, 5);
    PeriodicTaskInstance t2_secondInstance(
        t2, t2_firstInstance.activationTime + t2.period);

    PeriodicTaskInstance t3_firstInstance(t3, 9);
    PeriodicTaskInstance t3_fourthInstance(t3, 39);
    PeriodicTaskInstance t3_fifthInstance(
        t3, t3_fourthInstance.activationTime + t3.period);
    PeriodicTaskInstance t3_eighthInstance(
        t3, t3_fourthInstance.activationTime + t3.period * 4);

    std::vector<PeriodicTaskInstance> firstPath = {
        t1_firstInstance, t2_firstInstance, t3_fourthInstance};

    std::vector<PeriodicTaskInstance> secondPath = {
        t1_firstInstance, t2_firstInstance, t3_firstInstance};

    std::vector<PeriodicTaskInstance> thirdPath = {
        t1_thirdInstance, t2_secondInstance, t3_fifthInstance};

    std::vector<PeriodicTaskInstance> fourthPath = {
        t1_thirdInstance, t2_secondInstance, t3_eighthInstance};

    TimedPath firstTimedPath("First path", firstPath);
    TimedPath secondTimedPath("Second path", secondPath);
    TimedPath thirdTimedPath("Third path", thirdPath);
    TimedPath fourthTimedPath("Fourth path", fourthPath);

    // = delta_LF(secondTimedPath) + a(t1_thirdInstance) - a(t1_firstInstance) =
    // 10 + 40 - 0 = 50
    int expectedFirstToFirstDelay = 50;
    TimedPath expectedPath = secondTimedPath;

    std::multiset<TimedPath> paths = {firstTimedPath, secondTimedPath,
                                      thirdTimedPath, fourthTimedPath};

    // make sure both paths are reachable
    std::multiset<TimedPath> reachablePaths_LL = removeUnreachablePaths(paths);

    // this should remove the third path
    std::multiset<TimedPath> reachablePaths_LF =
        removePathsProducingDuplicateValues(reachablePaths_LL);

    int actualFirstToFirstDelay =
        analysis::getOverarchingDelay(reachablePaths_LF);

    EXPECT_EQ(expectedFirstToFirstDelay, actualFirstToFirstDelay);
}