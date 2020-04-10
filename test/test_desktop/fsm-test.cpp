#include <fsm.h>
#include "fake-callback.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace test
{
namespace
{
class FsmTest : public ::testing::Test
{
protected:
    mocks::FakeCallback _mockCallback;
};

TEST_F(FsmTest, should_be_correctly_initialized)
{
    fsm::Fsm aFsm;
    DEFINE_TRANSITION(aFsm, fsm::State::INIT, fsm::State::READY, fsm::Event::BEGIN, NULL);
    DEFINE_TRANSITION(aFsm, fsm::State::READY, fsm::State::DURATA, fsm::Event::DOWN, NULL);

    EXPECT_EQ(aFsm.getCurrentState(), fsm::State::INIT);
}

TEST_F(FsmTest, should_move_to_ready_state)
{
    int aFakeResourceManger;

    fsm::Fsm aFsm;
    aFsm.setResourceManger(&aFakeResourceManger);
    DEFINE_TRANSITION(aFsm, fsm::State::INIT, fsm::State::READY, fsm::Event::BEGIN, mocks::emptyCallback);
    DEFINE_TRANSITION(aFsm, fsm::State::READY, fsm::State::DURATA, fsm::Event::DOWN, mocks::emptyCallback);
    DEFINE_TRANSITION(aFsm, fsm::State::DURATA, fsm::State::DURATA, fsm::Event::ENTER, mocks::emptyCallback);
    aFsm.exec(fsm::Event::BEGIN);

    EXPECT_EQ(aFsm.getCurrentState(), fsm::State::READY);
}

TEST_F(FsmTest, should_exec_callback)
{
    EXPECT_CALL(_mockCallback, exec(testing::_)).Times(1);

    fsm::Fsm aFsm;
    aFsm.setResourceManger(&_mockCallback);
    DEFINE_TRANSITION(aFsm, fsm::State::INIT, fsm::State::READY, fsm::Event::BEGIN, mocks::fakeCallback);
    DEFINE_TRANSITION(aFsm, fsm::State::READY, fsm::State::DURATA, fsm::Event::DOWN, mocks::emptyCallback);
    DEFINE_TRANSITION(aFsm, fsm::State::DURATA, fsm::State::DURATA, fsm::Event::ENTER, mocks::emptyCallback);
    aFsm.exec(fsm::Event::BEGIN);
}
} // namespace
} // namespace test