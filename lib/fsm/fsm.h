#ifndef __FSM_H
#define __FSM_H

#ifndef UNIT_TEST
#include <Arduino.h>
#endif

namespace fsm
{
enum State
{
    INIT,
    MENU,
    SETTINGS,
    DURATA,
    TEMPERATURE,
    SETUP
};

enum Event
{
    BEGIN,
    UP,
    DOWN,
    ENTER,
    BACK,
    NO_EVENT
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
    int selectState(const fsm::Event iEvent) const;
    int exec(const fsm::Event iEvent);
    void addTransition(Transition iTransition);
    void setResourceManger(void *iResourceManager);
    void setCurrentState(fsm::State iState);

private:
    Transition *_states;
    size_t _statesLength = 0;
    fsm::State _currentState = State::INIT;
    void *_resourceManger;
};

} // namespace fsm
#endif