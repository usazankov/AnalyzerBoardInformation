#include "logsmanager.h"
int LogsManager::numbers_logs_file=0;
LogsManager::LogsManager(QObject *parent) : QObject(parent)
{
    file=new QFile(QString::number(numbers_logs_file++)+Ui::pathToLog);
    stream=new QDataStream(file);
    array=new QByteArray;
    buf=new QBuffer(array);
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
    else if(!blockBuf){
        (*stream_buf)<<time;
    }
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

void LogsManager::closeFile()
{
    if(!openedFile)
        file->close();
}

void LogsManager::read(int adress)
{
    reader->setAdress(adress);
    buf->open(QIODevice::WriteOnly);
    blockBuf=false;
    openedFile=true;
    file->close();
    thread->start();
}

void LogsManager::writeWord(unsigned int word)
{
    if(!openedFile)
        (*stream)<<word;
    else if(!blockBuf){
        (*stream_buf)<<word;
    }
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
    blockBuf=true;
    if(!file->exists())
        return;
    if(!file->open(QIODevice::WriteOnly|QIODevice::Append)){
        cout<<"Невозможно открыть файл\n";return;
    }
    buf->open(QIODevice::ReadOnly);
    if(array->size()!=0){
        unsigned int i;
        cout<<"array.size="<<array->size()<<endl;
        cout<<"seek="<<buf->seek(0)<<endl;
        while(!stream_buf->atEnd()){
            (*stream_buf)>>i;
            (*stream)<<i;
        }
        buf->close();
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
    QVector<TimeParametr> *vect=new QVector<TimeParametr>;
    cout<<"Opened File"<<endl;
    if(!file->exists()){
        emit data(vect);
        emit endToRead();
        return;
    }
    if(!file->open(QIODevice::ReadOnly)){
        cout<<"Невозможно открыть файл\n";
        //emit data(vect);
        //emit endToRead();
        return;
    }
    int size;
    (*stream_read)>>size;
    cout<<"size="<<size<<endl;
    double time;
    stream_read->setFloatingPointPrecision(QDataStream::DoublePrecision);
    (*stream_read)>>time;
    int count=0;
    double lastTime=0;
    //cout<<"time_read="<<time<<endl;

    double time_par;
    unsigned int par;
    while(!stream_read->atEnd()){
        if(count==size){
            (*stream_read)>>time;
            time_par=time;
            //cout<<"time_read="<<time<<endl;
            count=-1;
        }else{
            unsigned int i;
            (*stream_read)>>i;
            if((i&0xff)==adress)
                par=i;
                //cout<<"stream_read="<<i<<endl;
        }
        if(time-lastTime>=1.0){
            TimeParametr p;
            p.time=time_par;
            p.parametr=par;
            //cout<<"time_read="<<time_par<<endl;
            vect->push_back(p);
            lastTime=time;
        }
        ++count;
    }
    file->close();
    emit data(vect);
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
