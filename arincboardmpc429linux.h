#ifndef ARINCBOARDMPC429LINUX_H
#define ARINCBOARDMPC429LINUX_H
#include "readingbuffer.h"
namespace dev {
class ArincBoardlMPC429;
class ArincChannelMPC429;

}
class ArincBoardMPC429
{
public:
    explicit ArincBoardMPC429(const char *boardname, int MAX_NUMBER_CHANNEL);
    void stopBoard();//Остановить плату
    void closeBoard();//Закрыть устройство
    ~ArincBoardMPC429();
private:
    friend class ArincChannelMPC429;
    char* name;//Имя устройства
    int MAX_NUMBER_CHANNEL;
    int MIN_NUMBER_CHANNEL;
};

class ArincChannelMPC429: public ReadingBuffer<unsigned int*>
{
public:
    explicit ArincChannelMPC429(ArincBoardMPC429 *board,int number_channel,int number_bank);
    unsigned int* readBuffer();
    void Start();
    void Stop();
    int sizeOfBuffer()const;
    static int count;
private:
    ArincBoardMPC429 *board;
    int nc;
    int nb;
    static const int SIZE_BUF = 20;
    unsigned int buf[SIZE_BUF];
};

#endif // ARINCBOARDMPC429LINUX_H


