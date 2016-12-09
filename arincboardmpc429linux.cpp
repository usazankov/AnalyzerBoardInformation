#include "arincboardmpc429linux.h"


ArincBoardMPC429::ArincBoardMPC429(QString boardName, int index)
{
    this->name=boardName;
    this->MIN_NUMBER_CHANNEL=1;
    this->MAX_NUMBER_CHANNEL=8;
    this->i=index;
    cout<<"Создана Плата MPC429"<<" index="<<index<<" name="<<boardName.toStdString()<<endl;
}

void ArincBoardMPC429::stopBoard()
{

}

void ArincBoardMPC429::closeBoard()
{

}

ReadingBuffer<unsigned int *> *ArincBoardMPC429::createChannel(int number_channel, int number_bank)
{
    numbers_channel.push_back(number_channel);
    return new ArincChannelMPC429(this, number_channel, number_bank);
}

bool ArincBoardMPC429::containsChannel(int channel)
{
    return numbers_channel.contains(channel);
}

ArincBoardMPC429::~ArincBoardMPC429()
{
    stopBoard();
    closeBoard();
}

bool ArincBoardMPC429::BoardIsValid()
{
    int h = open(name.toStdString().c_str(), 0);
    if (h == -1)
    {
        close(h);
        return 1;
    }else {
        close(h);
        return 0;
    }
}

QString ArincBoardMPC429::getStatusBoard()
{
    int h = open(name.toStdString().c_str(), 0);
    if (h == -1)
    {
        close(h);
        return "Устройство не обнаружено";
    }else {
        close(h);
        return "Устройство обнаружено";
    }
}

QString ArincBoardMPC429::getDescriptionBoard()
{
    QString temp;
    int h=open(name.toStdString().c_str(), 0);
    short unsigned int d[32768];
    int rj;
    if (h == -1){
        close(h);
        temp="open error ";
        temp+=name;
        temp+=" (hArinc=-1)";
        return temp;
    }else{
        temp="SN0 = 0x";
        temp+=QString::number(d[0x1850],16);
        temp+="RJ0 = 0x"+QString::number(rj,16);
        temp+="RJ1 = 0x"+QString::number(rj,16);
        close(h);
        return temp;
    }
}

void ArincBoardMPC429::initArincBoard()
{

}

QString ArincBoardMPC429::boardName()
{
    return name;
}

int ArincChannelMPC429::count=0;

ArincChannelMPC429::ArincChannelMPC429(ArincBoardMPC429 *board, int number_channel, int number_bank)
{
    this->board=dynamic_cast<ArincBoardMPC429*>(board);
    nameArincBoard=board->boardName();
    if((number_channel<=this->board->MAX_NUMBER_CHANNEL)&&(number_channel>=this->board->MIN_NUMBER_CHANNEL)){
        nc=number_channel;
    }else{
        cout<<"Неверный номер канала (nc = "<<number_channel<<")"<<endl;
        throw bad_arinc_channel();
    }
    if(number_bank==0||number_bank==1){
        nb=number_bank;
    }else{
        cout<<"Неверный номер банка (nb = "<<number_bank<<")"<<endl;
        throw bad_arinc_channel();
    }
    for(int i=0;i<SIZE_BUF;i++){
        buf[i]=1;
    }
}

unsigned int *ArincChannelMPC429::readBuffer()
{
    int unsigned tword;
    for (int i=0;i<SIZE_BUF;i++){
        //READ_PRM_SS(hARINC, Data, nc, nb, i, tword);
        tword=i+9;
        buf[i]=tword;
    }
    return buf;
}

void ArincChannelMPC429::Start()
{

}

void ArincChannelMPC429::Stop()
{

}

int ArincChannelMPC429::sizeOfBuffer() const
{
    return SIZE_BUF;
}

QString ArincChannelMPC429::nameBoard() const
{
    return nameArincBoard;
}

ArincChannelMPC429::~ArincChannelMPC429()
{

}
