#ifndef DATA32_H
#define DATA32_H
#include "databehavior.h"
namespace params {
class DataArinc32;
}
class DataArinc32: public DataBehavior
{
public:
    DataArinc32(int word=0);
    void setPart(params::Part part, int value);
    bool Bit(int number_bit)const;
    void setBit(int number_bit, bool value);
    int PartAtBits(int begin, int end)const;
    int Part(params::Part)const;
    int LengthData()const;
    ~DataArinc32();
private:
    static const int LENGTH=32;
    union
    {
        unsigned int word;
        struct
        {
            unsigned int adress     :8;
                     int data       :22;
            unsigned int ms         :1;
            unsigned int parity     :1;
        };
    };
};


#endif // DATA32_H
