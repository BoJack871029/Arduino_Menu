#include <fsm.h>
#ifndef UNIT_TEST
#include <Arduino.h>
#else
#include <fake-lcd.h>
#include <iostream>
#endif

void fsm::Fsm::setResourceManger(void *iResourceManager)
{
    _resourceManger = iResourceManager;
}

void fsm::Fsm::setCurrentState(fsm::State iState)
{
    _currentState = iState;
}

fsm::State fsm::Fsm::getCurrentState()
{
    return _currentState;
}

void fsm::Fsm::addTransition(Transition iTransition)
{
    _states = (Transition *)realloc(_states, (_statesLength + 1) * sizeof(Transition));
    _states[_statesLength] = iTransition;
    _statesLength++;
}

int fsm::Fsm::selectState(const fsm::Event iEvent) const
{
    for (size_t i = 0; i < _statesLength; ++i)
    {
        Transition aTransition = _states[i];

        if (aTransition._currentState == _currentState && aTransition._event == iEvent)
        {
            return i;
        }
    }
    return -1;
}

int fsm::Fsm::exec(const fsm::Event iEvent)
{
    int aTransitionIndex = selectState(iEvent);

    if (aTransitionIndex > -1)
    {
        Transition aTransition = _states[aTransitionIndex];
        _currentState = aTransition._nextState;
        aTransition._callback(_resourceManger);
    }
    return 1;
}