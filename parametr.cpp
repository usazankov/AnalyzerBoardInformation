#include "parametr.h"
bool Parametr::ContainsBitFormat(Parametr::Format f) const
{
    return (bool)(format & f);
}

Parametr::Parametr()
{
    name="";
    dimension="";
    hasValue=0;
    setDefaultFormat();
}

Parametr::Parametr(QString Name,QString Dimension)
{
    name=Name;
    dimension=Dimension;
    hasValue=0;
    setDefaultFormat();
}

QString Parametr::Name()const
{
    if(name=="")return "Неизвестный параметр";
    return name;
}

QString Parametr::Dimension() const
{
    if(dimension=="")return "б/р";
    return dimension;
}

void Parametr::setUnpackValue(params::Part part, int value)
{
    db->setPart(part,value);
}

void Parametr::setFormat(int f)
{
    format=f;
}

void Parametr::setDefaultFormat()
{
    format=0;
    format=NameParametr|DimensionParametr|ValueParametr|StateParametr|MatrixStateParametr|UnpackValue|Adress;
}

void Parametr::setName(QString name)
{
    this->name=name;
}

void Parametr::setDimension(QString dim)
{
    this->dimension=dim;
}

void Parametr::setHasValue(bool flag)
{
    hasValue=flag;
}

void Parametr::setRegistered(bool flag)
{
    registered_flag=flag;
}

bool Parametr::HasValue() const
{
    return hasValue;
}

bool Parametr::registered() const
{
    return registered_flag;
}


QStringList Parametr::FormatAllValues()const
{
    QStringList list;
    if(ContainsBitFormat(Format::NameParametr))
        list.push_back(name);
    if(ContainsBitFormat(Format::DimensionParametr))
        list.push_back(dimension);
    return list;
}

QString Parametr::FormatValue(Parametr::Format f) const
{
    switch(f){
    case NameParametr:
        return Name();
        break;
    case DimensionParametr:
        return Dimension();
        break;
    default:
        return "-";
        break;
    }
}

Parametr::TypeParametr Parametr::Type()const
{
    return TypeParametr::NoType;
}



Parametr::~Parametr()
{
    delete db;
}
