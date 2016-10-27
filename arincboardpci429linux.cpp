#include "arincboardpci429linux.h"


ArincBoardlPCI429::ArincBoardlPCI429(const char *boardname, int MAX_NUMBER_CHANNEL)
{
    this->name=boardname;
    this->MIN_NUMBER_CHANNEL=1;
    this->MAX_NUMBER_CHANNEL=MAX_NUMBER_CHANNEL;
}

void ArincBoardlPCI429::initArincBoard()
{
    hARINC = open(name, 0);
    if (hARINC == -1)
    {
           cout<<"Ошибка подключения платы: open error ";
           cout<<name<<endl;
           flagInitBoard=false;
    }
    else{
        ioctl(hARINC,IOCTL_GET_SER_NUMBER ,Data);
        cout<<"Серийный номер платы: SN0 = 0x";
        cout<<hex<<Data[0x1850]<<endl;
        ioctl(hARINC,IOCTL_RJ ,Data);
        GET_RJ_M(Data,rj);
        cout<<"RJ0 = 0x"<<hex<<rj<<dec<<endl;
        GET_RJ(hARINC,Data,rj);
        cout<<"RJ1 = 0x"<<hex<<rj<<dec<<endl;
        SET_RM(Data,0x0);
        SET_RF_SI_N(Data,1,1,1,1,1,1,1,1);
        SET_RF_SO_N(Data,1,1,1,1,1,1,1,1);
        INIT_ARINC(hARINC,Data);
        cout<<"Плата инициализирована: ";
        cout<<name<<endl;
        flagInitBoard=true;
    }
}

void ArincBoardlPCI429::stopBoard()
{
    ARINC_STOP(hARINC, Data);
}

void ArincBoardlPCI429::closeBoard()
{
    close(hARINC);
}

bool ArincBoardlPCI429::BoardIsValid(const char *boardname)
{
    int h = open(boardname, 0);
    if (h == -1)
    {
        close(h);
        return 1;
    }else {
        close(h);
        return 0;
    }
}

QString ArincBoardlPCI429::getStatusBoard(const char *boardname)
{
    int h = open(boardname, 0);
    if (h == -1)
    {
        close(h);
        return "Устройство не обнаружено";
    }else {
        close(h);
        return "Устройство обнаружено";
    }

}

QString ArincBoardlPCI429::getDescriptionBoard(const char *boardname)
{
    QString temp;
    int h=open(boardname, 0);
    short unsigned int d[32768];
    int rj;
    if (h == -1){
        close(h);
        temp="open error ";
        temp+=QString(boardname);
        temp+=" (hArinc=-1)";
        return temp;
    }else{
        temp="SN0 = 0x";
        temp+=QString::number(d[0x1850],16);
        ioctl(h,IOCTL_RJ ,d);
        GET_RJ_M(d,rj);
        temp+="RJ0 = 0x"+QString::number(rj,16);
        GET_RJ(h,d,rj);
        temp+="RJ1 = 0x"+QString::number(rj,16);
        close(h);
        return temp;
    }

}

ArincBoardlPCI429::~ArincBoardlPCI429()
{

}


ArincChannelPCI429::ArincChannelPCI429(ArincBoardlPCI429 *board,int number_channel, int number_bank)
{
    this->board=board;
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

unsigned int *ArincChannelPCI429::readBuffer()
{
    int unsigned tword;
    for (int i=0;i<SIZE_BUF;i++){
        //READ_PRM_SS(hARINC, Data, nc, nb, i, tword);
        tword=i+199;
        buf[i]=tword;
    }
    return buf;
}

void ArincChannelPCI429::Start()
{
    SET_SI_TAB_Z(board->Data,nc,1,board->k);
    SET_SI_TAB(board->hARINC,board->Data,nc,1);
    PUSK_SI(board->hARINC,board->Data,nc,nb,1,0);
}

void ArincChannelPCI429::Stop()
{
    STOP_SI(board->hARINC, board->Data, nc);
}

int ArincChannelPCI429::sizeOfBuffer() const
{
    return SIZE_BUF;
}

ArincChannelPCI429::~ArincChannelPCI429()
{
    cout<<"DELETED!"<<endl;
}
