#include <task-runner.h>
#include <fake-callback.h>
#include "resource-manager.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace test
{
namespace
{
class TaskRunnerTest : public ::testing::Test
{
protected:
    mocks::FakeCallback _fakeCallback;
};

TEST_F(TaskRunnerTest, should_not_execute_task)
{
    EXPECT_CALL(_fakeCallback, exec(testing::_)).Times(0);
    resource::Manager aResourceManager;

    task::TaskRunner aTaskRunner(0, mocks::fakeCallback, &_fakeCallback);
    aTaskRunner.run(0, 10);

    EXPECT_EQ(0, aTaskRunner.getLastExecution());
}

TEST_F(TaskRunnerTest, should_execute_task)
{
    EXPECT_CALL(_fakeCallback, exec(testing::_)).Times(1);
    resource::Manager aResourceManager;

    task::TaskRunner aTaskRunner(0, mocks::fakeCallback, &_fakeCallback);
    aTaskRunner.run(10, 10);

    EXPECT_EQ(10, aTaskRunner.getLastExecution());
}

TEST_F(TaskRunnerTest, should_execute_task_once)
{
    EXPECT_CALL(_fakeCallback, exec(testing::_)).Times(1);
    resource::Manager aResourceManager;

    task::TaskRunner aTaskRunner(0, mocks::fakeCallback, &_fakeCallback);
    aTaskRunner.run(10, 10);
    aTaskRunner.run(11, 10);
    EXPECT_EQ(10, aTaskRunner.getLastExecution());
}

TEST_F(TaskRunnerTest, should_execute_task_twice)
{
    EXPECT_CALL(_fakeCallback, exec(testing::_)).Times(2);
    resource::Manager aResourceManager;

    task::TaskRunner aTaskRunner(0, mocks::fakeCallback, &_fakeCallback);
    aTaskRunner.run(10, 10);
    aTaskRunner.run(11, 10);
    aTaskRunner.run(20, 10);
    EXPECT_EQ(20, aTaskRunner.getLastExecution());
}

} // namespace
} // namespace test