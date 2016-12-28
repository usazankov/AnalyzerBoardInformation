#include "dataarinc32.h"

DataArinc32::DataArinc32(int word)
{
    this->word=word;
}

DataArinc32::DataArinc32(const DataArinc32 &d)
{
    this->word=d.word;
}

void DataArinc32::setPart(params::Part part, int value)
{
    switch (part) {
    case params::Part::Parity:
        parity=value;
        break;
    case params::Part::Adress:
        adress=value;
        break;
    case params::Part::MatrixState:
        ms=value;
        break;
    case params::Part::Value:
        data=value;
        break;
    case params::Part::TotalWord:
        word=value;
        break;
    default:
        word=value;
        break;
    }
}

bool DataArinc32::Bit(int number_bit)const
{
    if ((number_bit > 32) || (number_bit < 1)) return false;
    unsigned int mask = 1 << (number_bit - 1);
    bool result = (bool)(word & mask);
    return result;
}

void DataArinc32::setBit(int number_bit, bool value)
{
    unsigned int mask;
    if (value==0){
        mask=1<<(number_bit-1);
        mask=~mask;
        word=word&mask;
    }
    if(value==1){
        mask=1<<(number_bit-1);
        word=word|mask;
    }
}

int DataArinc32::PartAtBits(int begin, int end) const
{
    return 0;
}

int DataArinc32::Part(params::Part p) const
{
    switch (p) {
    case params::Part::Parity:
        return parity;
        break;
    case params::Part::Adress:
        return adress;
        break;
    case params::Part::MatrixState:
        return ms;
        break;
    case params::Part::Value:
        return data;
        break;
    case params::Part::TotalWord:
        return word;
        break;
    default:
        return word;
        break;
    }
}

int DataArinc32::LengthData()const
{
    return LENGTH;
}


DataArinc32::~DataArinc32()
{

}
