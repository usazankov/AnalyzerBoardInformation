#include "states.h"

int State::k=0;

State::State()
{
    namestate="";
    state1="";
    state0="";
    digit=0;
    k++;
}

State::State(const State &s)
{
    namestate=s.namestate;
    state1=s.state1;
    state0=s.state0;
    digit=s.digit;
    k++;
}

State::State(int digit, QString namestate, QString state0, QString state1)
{
    this->digit=digit;
    this->namestate=namestate;
    this->state0=state0;
    this->state1=state1;
    k++;
}

QString State::getNameState()
{
    return namestate;
}

QString State::getState0()
{
    return state0;
}

QString State::getState1()
{
    return state1;
}

void State::setState(int digit, QString namestate, QString state0, QString state1)
{
    this->digit=digit;
    this->namestate=namestate;
    this->state0=state0;
    this->state1=state1;
}

int State::getDigit()
{
    return digit;
}

State::~State()
{
    k--;
}

StateContanier::StateContanier()
{

}

void StateContanier::insertState(State *state)
{
    PtrsState.push_back(state);
}

State *StateContanier::getState(int index)
{
    return PtrsState[index];
}

int StateContanier::getSize()
{
    return PtrsState.size();
}

StateContanier::~StateContanier()
{
    for(int i=0;i<PtrsState.size();i++){
        delete PtrsState[i];
    }
}
