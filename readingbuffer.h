#ifndef READINGBUFFER_H
#define READINGBUFFER_H
namespace dev {
template<class TYPE> class ReadingBuffer;
}
template<class TYPE>
class ReadingBuffer
{
public:
    virtual TYPE readBuffer()=0;
    virtual int sizeOfBuffer()const=0;
    virtual void Start()=0;
    virtual void Stop()=0;
    virtual ~ReadingBuffer(){}
};

#endif // READINGBUFFER_H
