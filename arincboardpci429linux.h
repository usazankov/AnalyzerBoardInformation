#ifndef ARINCCHANNELPCI429LINUX_H
#define ARINCCHANNELPCI429LINUX_H
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
    explicit ArincBoardlPCI429(const char *boardname, int MAX_NUMBER_CHANNEL);
    void stopBoard();//Остановить плату
    void closeBoard();//Закрыть устройство
    static bool BoardIsValid(const char *boardname);
    static QString getStatusBoard(const char *boardname);
    static QString getDescriptionBoard(const char *boardname);
    void initArincBoard();//Инициализировать плату
    ~ArincBoardlPCI429();
private:
    friend class ArincChannelPCI429;
    int k, rj;//Служебные переменные
    short unsigned int Data[32768];//Массив данных для обмена с платой
    int hARINC;//Дескриптор устройства
    const char* name;//Имя устройства
    bool flagInitBoard;
    int MAX_NUMBER_CHANNEL;
    int MIN_NUMBER_CHANNEL;
};

class ArincChannelPCI429 : public ReadingBuffer<unsigned int*>
{
public:
    explicit ArincChannelPCI429(ArincBoardlPCI429* board, int number_channel, int number_bank);
    unsigned int* readBuffer();//Считать буфер данных
    void Start();//Запустить канал приема
    void Stop();//Остановить канал приема
    int sizeOfBuffer()const;//Размер буфера
    class bad_arinc_channel{};
    ~ArincChannelPCI429();
private:
    ArincBoardlPCI429 *board;
    int nc;
    int nb;
    static const int SIZE_BUF = 20;
    unsigned int buf[SIZE_BUF];

};

#endif // ARINCCHANNELPCI429LINUX_H
