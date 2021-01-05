#include "StateMachine.h"

StateMachine::StateMachine()
    : m_isAdding( false ), m_isReplacing( false ), m_isRemoving( false )
{

}

StateMachine::~StateMachine()
{

}

void StateMachine::AddState( StateRef newState, bool isReplacing )
{
    this->m_isAdding = true;
    this->m_isReplacing = isReplacing;

    this->m_newState = std::move( newState );
}

void StateMachine::RemoveState()
{
    this->m_isRemoving = true;
}

void StateMachine::ProcessStateChange()
{
    if( this->m_isRemoving && ( !this->m_states.empty() ) )
    {
        this->m_states.pop();

        if( !this->m_states.empty() )
            this->m_states.top()->Resume();
        this->m_isRemoving = false;
    }

    if( this->m_isAdding )
    {
        if( this->m_isReplacing && ( !this->m_states.empty() ) )
        {
            this->m_states.pop();
            this->m_isReplacing = false;
        }
        if( !this->m_states.empty() )
            this->m_states.top()->Pause();

        this->m_states.push( std::move( this->m_newState ) );
        this->m_states.top()->Init();
        this->m_states.top()->Resume();
        this->m_isAdding = false;
    }
}

void StateMachine::PopState()
{
    this->m_states.pop();
}

StateRef& StateMachine::GetActiveState()
{
    return this->m_states.top();
}


void StateMachine::ChangeState()
{
    this->m_states.pop();
    this->m_states.push( std::move( GetActiveState() ) );
}