#include "arincparametr.h"
int ArincParametr::count=0;

ArincParametr::ArincParametr(int word):Parametr()
{
    db=new DataArinc32(word);
    ++count;
}

ArincParametr::ArincParametr(int word, QString Name, QString Dimension):Parametr(Name,Dimension)
{
    db=new DataArinc32(word);
    ++count;
}

void ArincParametr::setWord(int word)
{
    db->setPart(params::Part::TotalWord,word);
}

int ArincParametr::Adress() const
{
    return db->Part(params::Part::Adress);
}

int ArincParametr::MatrixState() const
{
    int ms=db->Part(params::Part::MatrixState);
    if(db->Bit(30)==1&&ms==1)return 3;
    if(db->Bit(30)==1&&ms==0)return 1;
    if(db->Bit(30)==0&&ms==1)return 2;
    if(db->Bit(30)==0&&ms==0)return 0;
    return 0;
}

int ArincParametr::UnpackWord() const
{
    return db->Part(params::Part::TotalWord);
}

Parametr::TypeParametr ArincParametr::Type() const
{
    return TypeParametr::ARINC_PARAM;
}

QStringList ArincParametr::FormatAllValues() const
{
    QStringList list;
    return list;
}

QString ArincParametr::FormatValue(Parametr::Format f) const
{
    int matrix;
    switch(f){
    case NameParametr:
        return Name();
        break;
    case DimensionParametr:
        return Dimension();
        break;
    case MatrixStateParametr:
        matrix=MatrixState();
        if(matrix==0)return "00";
        else if(matrix==1)return "01";
        else if(matrix==2)return "10";
        else if(matrix==3)return "11";
        else return "-";
        break;
    case Parametr::Adress:
        return "0"+QString::number(Adress(),8);
        break;
    case UnpackValue:
        if(HasValue()==1)
            return "0x"+QString::number(UnpackWord(),16);
        else return "Слово отсутствует";
        break;
    default:
        if(HasValue()==1)
            return "-";
        else return "Слово отсутствует";
        break;
    }
}

ArincParametr::~ArincParametr()
{
    --count;
}

ArincDecParametr::ArincDecParametr(int word,double UnpackConst):ArincParametr(word)
{
    unpack_const=UnpackConst;
}

ArincDecParametr::ArincDecParametr(int word, QString name, QString Dimension, double UnpackConst):ArincParametr(word, name, Dimension)
{
    unpack_const=UnpackConst;
}

double ArincDecParametr::Value()const
{
    if(db->Bit(30)==1&&db->Part(params::Part::MatrixState)==0){
        db->setBit(30,0);
        double temp=((double)((db->Part(params::Part::Value)))*unpack_const/params::ARINC_SCALE);
        db->setBit(30,1);
        return temp;
    }else
    return (double)((db->Part(params::Part::Value)*unpack_const/params::ARINC_SCALE));
}

void ArincDecParametr::setUnpackConst(double unpack_const)
{
    this->unpack_const=unpack_const;
}

double ArincDecParametr::getUnpackConst() const
{
    return unpack_const;
}

QString ArincDecParametr::FormatValue(Parametr::Format f) const
{
    if(ArincParametr::FormatValue(f)=="-"){
        if(f==ValueParametr)
            return QString::number(Value());
        else return "-";
    }else return ArincParametr::FormatValue(f);
}

QStringList ArincDecParametr::FormatAllValues() const
{
    QStringList list;
    if(ContainsBitFormat(Format::NameParametr))
        list.push_back(Name());
    if(ContainsBitFormat(Format::ValueParametr))
        list.push_back(QString::number(Value()));
    if(ContainsBitFormat(Format::DimensionParametr))
        list.push_back(Dimension());
    if(ContainsBitFormat(Format::MatrixStateParametr)){
        list.push_back(QString::number(MatrixState()));
    }
    if(ContainsBitFormat(Format::Adress)){
        list.push_back(FormatValue(Format::Adress));
    }
    if(ContainsBitFormat(Format::UnpackValue))
        list.push_back("0x"+QString::number(UnpackWord(),16));
    return list;
}

Parametr::TypeParametr ArincDecParametr::Type() const
{
    return TypeParametr::ARINC_DEC;
}

ArincDecParametr::~ArincDecParametr()
{

}

int ArincDiscrParametr::k=0;

ArincDiscrParametr::ArincDiscrParametr(int word):ArincParametr(word)
{
    states=NULL;
    k++;
}

ArincDiscrParametr::ArincDiscrParametr(int word, QString Name):ArincParametr(word, Name)
{
    states=NULL;
    k++;
}

ArincDiscrParametr::ArincDiscrParametr(int word, StateContanier *sc):ArincParametr(word)
{
    setStates(sc);
    states=NULL;
    k++;
}

ArincDiscrParametr::ArincDiscrParametr(int word, QString Name, StateContanier *sc):ArincParametr(word, Name)
{
    setStates(sc);
    k++;
}

QString ArincDiscrParametr::displayStates() const
{
    QString temp_string="";
    if(hasStates()){
        for(int i=0;i<states->getSize();i++){
            State *temp=states->getState(i);
            temp_string+=temp->getNameState();
            if(db->Bit(temp->getDigit())==1)temp_string+=temp->getState1();
                else temp_string+=temp->getState0();
            //if(i!=states->getSize()-1)
            temp_string+="\n";
        }
        return temp_string;
    }else return temp_string+"-";
}

QStringList ArincDiscrParametr::getStates() const
{
    QStringList temp_stringlist;
    if(hasStates()){
        for(int i=0;i<states->getSize();i++){
            State *temp=states->getState(i);
            temp_stringlist.push_back(temp->getNameState());
            if(db->Bit(temp->getDigit())==1)temp_stringlist.push_back(temp->getState1());
                else temp_stringlist.push_back(temp->getState0());
        }
        return temp_stringlist;
    }else return temp_stringlist;
}

void ArincDiscrParametr::setStates(StateContanier *sc)
{
    states=sc;
}

QString ArincDiscrParametr::FormatValue(Parametr::Format f) const
{
    if(ArincParametr::FormatValue(f)=="-"){
        if(f==StateParametr)
            return displayStates();
        else return "-";
    }else return ArincParametr::FormatValue(f);
}

QStringList ArincDiscrParametr::getNameStates() const
{
    QStringList temp_stringlist;
    if(hasStates()){
        for(int i=0;i<states->getSize();i++){
            State *temp=states->getState(i);
            temp_stringlist.push_back(temp->getNameState());
        }
        return temp_stringlist;
    }else return temp_stringlist;
}

QStringList ArincDiscrParametr::getValueStates() const
{
    QStringList temp_stringlist;
    if(hasStates()){
        for(int i=0;i<states->getSize();i++){
            State *temp=states->getState(i);
            if(db->Bit(temp->getDigit())==1)temp_stringlist.push_back(temp->getState1());
                else temp_stringlist.push_back(temp->getState0());
        }
        return temp_stringlist;
    }else return temp_stringlist;
}

QStringList ArincDiscrParametr::FormatAllValues() const
{
    QStringList list;
    if(ContainsBitFormat(Format::NameParametr))
        list.push_back(Name());
    if(ContainsBitFormat(Format::MatrixStateParametr))
        list.push_back(FormatValue(Format::MatrixStateParametr));
    if(ContainsBitFormat(Format::StateParametr))
        list+=getStates();
    if(ContainsBitFormat(Format::Adress)){
        list.push_back(FormatValue(Format::Adress));
    }
    if(ContainsBitFormat(Format::UnpackValue))
        list.push_back("0x"+QString::number(UnpackWord(),16));
    return list;
}

Parametr::TypeParametr ArincDiscrParametr::Type() const
{
    return TypeParametr::ARINC_DISCR;
}

bool ArincDiscrParametr::hasStates() const
{
    if(states!=0)return true;
    else return false;
}

ArincDecDiscrParametr::ArincDecDiscrParametr(int word)
{

}

ArincDecDiscrParametr::ArincDecDiscrParametr(int word, QString name)
{

}
