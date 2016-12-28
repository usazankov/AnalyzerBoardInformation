#include "logsmanager.h"



LogsManager::LogsManager(QObject *parent) : QObject(parent)
{
    file=new QFile(Ui::pathToLog);
    stream=new QDataStream(file);
    array=new QByteArray;
    buf=new QBuffer(array);
    buf->open(QIODevice::ReadWrite);
    stream_buf=new QDataStream(buf);
    thread=new QThread;
    reader=new FileReader(file);
    reader->moveToThread(thread);
    connect(thread,SIGNAL(started()),reader,SLOT(read()));
    connect(reader,SIGNAL(endToRead()),thread,SLOT(quit()));
    connect(reader,SIGNAL(endToRead()),this,SLOT(applyBuffer()));
    sizeBufWrited=false;
    stream->setFloatingPointPrecision(QDataStream::DoublePrecision);
}

void LogsManager::writeTime(double time)
{
    if(!openedFile)
        (*stream)<<time;
    else
        (*stream_buf)<<time;
}

void LogsManager::writeSizeBuf(unsigned int size)
{
    if(!sizeBufWrited){
        sizeBuf=size;
        (*stream)<<size;
        sizeBufWrited=true;
    }
}

void LogsManager::openFile()
{
    if(!openedFile&&(!file->isOpen()))
        if(!file->open(QIODevice::WriteOnly|QIODevice::Append)){
            cout<<"Невозможно открыть файл\n";return;
        }
}

void LogsManager::flushFile()
{
    file->flush();
    file->close();
}

void LogsManager::closeFile()
{
    if(!openedFile)
        file->close();
}

void LogsManager::read(int adress)
{
    reader->setAdress(adress);
    openedFile=true;
    file->close();
    thread->start();
}

void LogsManager::writeWord(unsigned int word)
{
    if(!openedFile)
        (*stream)<<word;
    else
        (*stream_buf)<<word;
}

int LogsManager::sizeBuffer() const
{

}

LogsManager::~LogsManager()
{
    delete stream;
    delete buf;
    delete array;
    delete stream_buf;
    delete file;
    delete thread;
    delete reader;
}

void LogsManager::applyBuffer()
{
    if(!file->open(QIODevice::WriteOnly|QIODevice::Append)){
        cout<<"Невозможно открыть файл\n";return;
    }
    if(array->size()!=0){
        unsigned int i;
        cout<<"array.size="<<array->size()<<endl;
        cout<<"seek="<<buf->seek(0)<<endl;
        while(!stream_buf->atEnd()){
                (*stream_buf)>>i;
                (*stream)<<i;
        }
        array->clear();
        cout<<"array.size="<<array->size()<<endl;
    }
    openedFile=false;
}


FileReader::FileReader(QFile *file, QObject *parent):QObject(parent)
{
    this->file=file;
    stream_read=new QDataStream(file);
}

void FileReader::read()
{
    QVector<TimeParametr> vect;
    cout<<"Opened File"<<endl;
    if(!file->open(QIODevice::ReadOnly)){
        cout<<"Невозможно открыть файл\n";return;
    }

    int size;
    (*stream_read)>>size;
    cout<<"size="<<size<<endl;
    double time;
    stream_read->setFloatingPointPrecision(QDataStream::DoublePrecision);
    (*stream_read)>>time;
    int count=0;
    int k=1;
    cout<<"time_read="<<time<<endl;
    TimeParametr p;
    p.time=time;
    while(!stream_read->atEnd()){
        if(count==size){
            (*stream_read)>>time;
            p.time=time;
            cout<<"time_read="<<time<<endl;
            count=-1;
            k=1;
        }else{
            unsigned int i;
            (*stream_read)>>i;
            p.parametr=i;
            //if((i&0xff)==adress)
                //cout<<"count="<<k++<<endl;
                //cout<<"stream_read="<<i<<endl;

        }
        vect.push_back(p);
        ++count;
    }
    file->close();
    emit endToRead();
}

void FileReader::setAdress(int adress)
{
    this->adress=adress;
}


FileReader::~FileReader()
{
    delete stream_read;
}
