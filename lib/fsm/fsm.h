#ifndef __FSM_H
#define __FSM_H

#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include "arduino-desktop.h"
#endif

#define DEFINE_TRANSITION(FSM, FROM, TO, EVENT, FUNCTION) \
    {                                                     \
        FSM.addTransition({FROM, TO, EVENT, FUNCTION});   \
    }

namespace fsm
{
enum State
{
    INIT,
    MENU,
    SETTINGS,
    DURATA,
    TEMPERATURE,
    SETUP,
    READY
};

enum Event
{
    BEGIN,
    UP,
    DOWN,
    ENTER,
    BACK,
    NO_EVENT,
    OPEN_MENU
};

struct Transition
{
    State _currentState;
    State _nextState;
    Event _event;
    void (*_callback)(void *);

    State *getCurrentState()
    {
        return &_currentState;
    }
};

class Fsm
{
public:
    int exec(const fsm::Event iEvent);
    void addTransition(Transition iTransition);
    void setResourceManger(void *iResourceManager);
    void setCurrentState(fsm::State iState);
    fsm::State getCurrentState();

private:
    int selectState(const fsm::Event iEvent) const;
    Transition *_states = NULL;
    size_t _statesLength = 0;
    fsm::State _currentState = State::INIT;
    void *_resourceManger;
};

} // namespace fsm
#endif