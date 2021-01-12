#pragma once

#include <memory>
#include <stack>
#include <map>

#include "State.h"

typedef std::unique_ptr< State > StateRef;

class StateMachine{
public:
    StateMachine();
    ~StateMachine();

    void AddState( StateRef newState, bool isReplacing = false );
    void RemoveState();

    void PopState();

    void ProcessStateChange();

    StateRef& GetActiveState();

    void ChangeState();

private:
    std::stack< StateRef > m_states;
    StateRef m_newState;

    bool m_isRemoving;
    bool m_isAdding;
    bool m_isReplacing;
};