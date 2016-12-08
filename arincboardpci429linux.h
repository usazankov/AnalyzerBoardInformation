#ifndef ARINCBOARDPCI429LINUX_H
#define ARINCBOARDPCI429LINUX_H
#include "readingbuffer.h"
#include "pci429LNX.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <QMap>
namespace dev {
    class ArincBoardlPCI429;
    class ArincChannelPCI429;
    enum TypeBoard{ArincPCI429,ArincMPC429};
}
using namespace std;
class ArincBoardlPCI429
{
public:
    explicit ArincBoardlPCI429(QString boardname, int index);
    void stopBoard();//Остановить плату
    void closeBoard();//Закрыть устройство
    static bool BoardIsValid(QString boardname);
    static QString getStatusBoard(QString boardname);
    static QString getDescriptionBoard(QString boardname);
    void initArincBoard();//Инициализировать плату
    QString boardName();
    ~ArincBoardlPCI429();
private:
    friend class ArincChannelPCI429;
    int k, rj;//Служебные переменные
    short unsigned int Data[32768];//Массив данных для обмена с платой
    int hARINC;//Дескриптор устройства
    QString name;//Имя устройства
    bool flagInitBoard;
    int MAX_NUMBER_CHANNEL;
    int MIN_NUMBER_CHANNEL;
    int index;
};

class ArincChannelPCI429 : public ReadingBuffer<unsigned int*>
{
public:
    explicit ArincChannelPCI429(ArincBoardlPCI429* board, int number_channel, int number_bank,int index);
    unsigned int* readBuffer();//Считать буфер данных
    void Start();//Запустить канал приема
    void Stop();//Остановить канал приема
    int sizeOfBuffer()const;//Размер буфера
    static int count;
    int indexChannel();
    class bad_arinc_channel{};
    ~ArincChannelPCI429();
private:
    ArincBoardlPCI429 *board;
    int nc;
    int nb;
    int index;
    static const int SIZE_BUF = 20;
    unsigned int buf[SIZE_BUF];
};

#endif // ARINCBOARDPCI429LINUX_H
