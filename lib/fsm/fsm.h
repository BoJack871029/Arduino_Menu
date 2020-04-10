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
    OPEN_MENU,
    READ_EEPROM,
    WRITE_EEPROM
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
    virtual int exec(const fsm::Event iEvent);
    virtual void addTransition(Transition iTransition);
    virtual void setResourceManger(void *iResourceManager);
    virtual void setCurrentState(fsm::State iState);
    virtual fsm::State getCurrentState();

private:
    int selectState(const fsm::Event iEvent) const;
    Transition *_states = NULL;
    size_t _statesLength = 0;
    fsm::State _currentState = State::INIT;
    void *_resourceManger;
};

} // namespace fsm
#endif