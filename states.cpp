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

QString State::getNameState() const
{
    return namestate;
}

QString State::getState0()const
{
    return state0;
}

QString State::getState1()const
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

void State::setNameState(QString namestate)
{
    this->namestate=namestate;
}

void State::setDigit(int digit)
{
    this->digit=digit;
}

void State::setState0(QString state0)
{
    this->state0=state0;
}

void State::setState1(QString state1)
{
    this->state1=state1;
}

int State::getDigit()const
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

void StateContanier::deleteState(int index)
{
    delete PtrsState.at(index);
    PtrsState.removeAt(index);
}

State *StateContanier::getState(int index) const
{
    return PtrsState.at(index);
}

State *StateContanier::getState_to_change(int index)
{
    return PtrsState.at(index);
}

int StateContanier::getSize()const
{
    return PtrsState.size();
}

StateContanier::~StateContanier()
{
    for(int i=0;i<PtrsState.size();i++){
        delete PtrsState.at(i);
    }
}
