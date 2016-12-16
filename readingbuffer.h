#ifndef READINGBUFFER_H
#define READINGBUFFER_H
#include <QString>
namespace dev {
template<class TYPE> class ReadingBuffer;
class ArincBoardInterface;
}
template<class TYPE>
class ReadingBuffer
{
public:
    virtual TYPE readBuffer()=0;
    virtual int sizeOfBuffer()const=0;
    virtual void Start()=0;
    virtual void Stop()=0;
    virtual QString name()const=0;
    virtual int index()const=0;
    virtual ~ReadingBuffer(){}
};

class ArincBoardInterface{
public:
    virtual void stopBoard()=0;//Остановить плату
    virtual void closeBoard()=0;//Закрыть устройство
    virtual bool BoardIsValid()=0;
    virtual ReadingBuffer<unsigned int*>* createChannel(int number_channel,int number_bank)=0;
    virtual void deleteChannel(int number_channel)=0;
    virtual bool containsChannel(int channel)=0;
    virtual QString getStatusBoard()=0;
    virtual QString getDescriptionBoard()=0;
    virtual void initArincBoard()=0;//Инициализировать плату
    virtual QString boardName()=0;
    virtual ~ArincBoardInterface(){}
};
#endif // READINGBUFFER_H
