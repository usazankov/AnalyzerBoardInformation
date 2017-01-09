#ifndef DATABEHAVIOR_H
#define DATABEHAVIOR_H

namespace params {
enum Part{Parity, MatrixState, Value, Adress, TotalWord};
/* PartArinc - состав слова в соответствии с протоколом ARINC-429
 * Parity - паритетный бит
 * MatrixState - матрица состояния
 * Value - числовая часть слова
 * Adress - адрес слова*/
}
class DataBehavior
{
public:
    virtual void setBit(int number_bit, bool value)=0;//Задать значение бита
    virtual bool Bit(int number_bit)const=0 ;//Получить значение бита по номеру
    virtual int PartAtBits(int begin,int end)const=0 ;//Получить часть данных начиная от начального номера бита begin до номера end
    virtual int Part(params::Part p)const=0;//Получить часть данных
    virtual void setPart(params::Part part,int value)=0;
    virtual int LengthData()const=0;//Длина данных в битах
    virtual ~DataBehavior(){}
};

#endif // DATABEHAVIOR_H
