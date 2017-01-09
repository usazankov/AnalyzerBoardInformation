#ifndef ARINCBOARDMPC429LINUX_H
#define ARINCBOARDMPC429LINUX_H
#include "arincintefaces.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <QMap>
namespace dev {
class ArincBoardlMPC429;
class ArincChannelMPC429;

}
using namespace std;
class ArincChannelMPC429;
class ArincBoardMPC429:public ArincBoardInterface
{
public:
    explicit ArincBoardMPC429(QString boardName, int index);
    void stopBoard();
    void closeBoard();
    ReadingBuffer<unsigned int *> *createChannel(int channel, int number_bank);
    void deleteChannel(int channel);
    bool containsChannel(int channel);
    bool BoardIsValid();
    QString getStatusBoard();//Обнаружено ли устройство
    QString getDescriptionBoard();
    void initArincBoard();
    QString boardName();

    ~ArincBoardMPC429();
private:
    friend class ArincChannelMPC429;
    int i;//индекс платы
    QMap<int,ReadingBuffer<unsigned int *>*> numbers_channel;//Контейнер созданных каналов
    QString name;//Имя устройства
    int MAX_NUMBER_CHANNEL;
    int MIN_NUMBER_CHANNEL;


    // ArincBoardInterface interface
public:
    void deleteAllChannel();
};

class ArincChannelMPC429: public ReadingBuffer<unsigned int*>
{
public:
    explicit ArincChannelMPC429(ArincBoardMPC429 *board,int number_channel,int number_bank);
    unsigned int* readBuffer();
    void Start();
    void Stop();
    int sizeOfBuffer()const;
    QString name()const;
    int index()const;
    static int count;
    class bad_arinc_channel{};
    ~ArincChannelMPC429();
private:
    ArincBoardMPC429 *board;
    QString nameArincBoard;

    int nc;
    int nb;
    static const int SIZE_BUF = 3;
    unsigned int buf[SIZE_BUF];
};

#endif // ARINCBOARDMPC429LINUX_H


