#ifndef ARINCBOARDPCI429LINUX_H
#define ARINCBOARDPCI429LINUX_H
#include "readingbuffer.h"
#include "pci429LNX.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <QMap>
#include <QVector>
namespace dev {
    class ArincBoardlPCI429;
    class ArincChannelPCI429;
    enum TypeBoard{ArincPCI429,ArincMPC429};
}
using namespace std;
class ArincChannelPCI429;
class ArincBoardlPCI429: public ArincBoardInterface
{
public:
    explicit ArincBoardlPCI429(QString boardname, int index);
    // ArincBoardInterface interface
    void stopBoard();//Остановить плату
    void closeBoard();//Закрыть устройство
    bool BoardIsValid();
    ReadingBuffer<unsigned int *> *createChannel(int channel, int number_bank);
    bool containsChannel(int channel);
    QString getStatusBoard();
    QString getDescriptionBoard();
    void initArincBoard();//Инициализировать плату
    QString boardName();
    ~ArincBoardlPCI429();
private:
    friend class ArincChannelPCI429;
    int k, rj;//Служебные переменные
    short unsigned int Data[32768];//Массив данных для обмена с платой
    int hARINC;//Дескриптор устройства
    QString name;//Имя устройства
    QMap<int,ReadingBuffer<unsigned int *>*> numbers_channel;
    bool flagInitBoard;
    int MAX_NUMBER_CHANNEL;
    int MIN_NUMBER_CHANNEL;
    int index;


    // ArincBoardInterface interface
public:
    void deleteChannel(int number_channel);

    // ArincBoardInterface interface
public:
    void deleteAllChannel();
};

class ArincChannelPCI429 : public ReadingBuffer<unsigned int*>
{
public:
    explicit ArincChannelPCI429(ArincBoardInterface* board, int number_channel, int number_bank);
    unsigned int* readBuffer();//Считать буфер данных
    void Start();//Запустить канал приема
    void Stop();//Остановить канал приема
    int sizeOfBuffer()const;//Размер буфера
    QString name()const;
    int index()const;
    static int count;
    class bad_arinc_channel{};
    ~ArincChannelPCI429();
private:
    ArincBoardlPCI429 *board;
    QString nameArincBoard;
    bool started;
    int nc;
    int nb;
    static const int SIZE_BUF = 255;
    unsigned int buf[SIZE_BUF];
};

#endif // ARINCBOARDPCI429LINUX_H
