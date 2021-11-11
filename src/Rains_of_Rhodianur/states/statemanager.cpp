#include "statemanager.h"

void StateManager::addState(state_ptr stateAdded, bool replace)
{
    this->add = true;
    this->replace = replace;
    this->newState = std::move(stateAdded);
}

void StateManager::popState()
{
    this->remove = true;
}

void StateManager::changeState()
{
    if(this->remove && !this->states.empty())
    {
        this->states.pop();

        if(!this->states.empty())
        {
            this->states.top()->Resume();

        }

        this->remove = false;
    }

    if(this->add)
    {
        if(this->replace && !this->states.empty())
        {
            this->states.pop();
        }

        if(!this->states.empty())
        {
            this->states.top()->Pause();
        }

        this->states.push(std::move(this->newState));
        this->states.top()->Init();
        this->add = false;
    }
}

state_ptr &StateManager::getCurrentState()
{
    return this->states.top();
}