#pragma once

#include <memory>
#include <stack>

#include "State.h"

typedef std::unique_ptr< State > StateRef;

class StateMachine{
public:
    StateMachine(){}
    ~StateMachine(){}

    void AddState( StateRef newState, bool isReplacing = true );
    void RemoveState();

    void ProcessStateChange();

    StateRef& GetActiveState();

private:
    std::stack< StateRef > m_states;
    StateRef m_newState;

    bool m_isRemoving;
    bool m_m_isAdding;
    bool m_isReplacing;
};