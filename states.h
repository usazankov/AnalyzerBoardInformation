#ifndef STATES_H
#define STATES_H
#include <QList>
#include <iostream>
namespace params {
class State;
class StateContanier;
}
using namespace std;
class State{
public:
    State();
    State(const State& s);
    State(int digit,QString namestate,QString state0,QString state1);
    QString getNameState()const;
    QString getState0()const;
    QString getState1()const;
    void setState(int digit,QString namestate,QString state0,QString state1);
    void setNameState(QString namestate);
    void setDigit(int digit);
    void setState0(QString state0);
    void setState1(QString state1);
    int getDigit()const;
    ~State();
    static int k;
private:
    QString namestate;
    QString state1;
    QString state0;
    int digit;
};

class StateContanier
{
public:
    StateContanier();
    StateContanier(const StateContanier& states);
    void insertState(State *state);
    void deleteState(int index);
    State *getState(int index)const;
    void setNameState(QString namestate,int index);
    void setDigit(int digit,int index);
    void setState0(QString state0,int index);
    void setState1(QString state1,int index);
    int getSize() const;
    StateContanier& operator = (const StateContanier& cont);
    bool isEmptyContanier()const;
    ~StateContanier();
private:
    QList<State*> PtrsState;
};

#endif // STATES_H
