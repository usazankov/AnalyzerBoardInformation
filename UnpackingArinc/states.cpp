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

StateContanier::StateContanier(const StateContanier &states)
{
    foreach (State *s, states.PtrsState){
        State *state=new State(*s);
        PtrsState.push_back(state);
    }
}

void StateContanier::insertState(State *state)
{
    PtrsState.push_back(state);
}

void StateContanier::deleteState(int index)
{
    PtrsState.removeAt(index);
}

State *StateContanier::getState(int index) const
{
    return PtrsState.at(index);
}

void StateContanier::setNameState(QString namestate, int index)
{
    PtrsState.at(index)->setNameState(namestate);
}

void StateContanier::setDigit(int digit, int index)
{
    PtrsState.at(index)->setDigit(digit);
}

void StateContanier::setState0(QString state0, int index)
{
    PtrsState.at(index)->setState0(state0);
}

void StateContanier::setState1(QString state1, int index)
{
    PtrsState.at(index)->setState1(state1);
}



bool StateContanier::isEmptyContanier() const
{
    return PtrsState.empty();
}

int StateContanier::getSize()const
{
    return PtrsState.size();
}

StateContanier &StateContanier::operator =(const StateContanier &cont)
{
    if(!PtrsState.isEmpty()){
        while(!PtrsState.empty()){
            delete PtrsState.back();
            PtrsState.pop_back();
        }
    }
    foreach (State *s, cont.PtrsState){
        State *state=new State(*s);
        PtrsState.push_back(state);
    }
    return *this;
}

StateContanier::~StateContanier()
{
    if(!PtrsState.isEmpty()){
        while(!PtrsState.empty()){
            delete PtrsState.back();
            PtrsState.pop_back();
        }
    }
}
