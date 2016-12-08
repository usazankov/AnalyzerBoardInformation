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
    void insertState(State *state);
    void deleteState(int index);
    State* getState(int index)const;
    State *getState_to_change(int index);
    int getSize() const;
    ~StateContanier();
private:
    QList<State*> PtrsState;
};

#endif // STATES_H
