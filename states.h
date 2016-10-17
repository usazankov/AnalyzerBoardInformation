#ifndef STATES_H
#define STATES_H
#include <QVector>
namespace params {
class State;
class StateContanier;
}
class State{
public:
    State();
    State(const State& s);
    State(int digit,QString namestate,QString state0,QString state1);
    QString getNameState();
    QString getState0();
    QString getState1();
    void setState(int digit,QString namestate,QString state0,QString state1);
    int getDigit();
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
    void insertState(State *state);
    State* getState(int index);
    int getSize();
    ~StateContanier();
private:
    QVector<State*> PtrsState;
};

#endif // STATES_H
