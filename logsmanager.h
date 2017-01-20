#ifndef LOGSMANAGER_H
#define LOGSMANAGER_H

#include <QObject>
#include <QDataStream>
#include <QBuffer>
#include <QFile>
#include <QThread>
#include <QVector>
#include <iostream>
#include <QDir>
#include <QDateTime>
#include "arincmodelinterface.h"
namespace Ui {
    const QString DefaultNameDirLogs="/Logs";
    const QString NameTemporary="/temp";
    const int SIZE_BUFFER_TO_LOG=5;
}
using namespace std;
class FileReader : public QObject{
    Q_OBJECT
public:
    explicit FileReader(QFile *file, QObject* parent=0);
    void setAdress(int adress);
    ~FileReader();
public slots:
    void read();
signals:
    void endToRead();
    void data(QVector<TimeParametr> *p);
private:
    QFile *file;
    QDataStream *stream_read;
    int adress;
};
class LogsManager : public QObject
{
    Q_OBJECT
private:
    QDataStream *stream;
    QBuffer *buf;
    QByteArray *array;
    QDataStream *stream_buf;
    QFile *file;
    QThread *thread;
    QDir current_dir;
    static int numbers_logs_file;
    bool openedFile;
    bool sizeBufWrited;
    bool blockBuf;
    int sizeBuf;
public:
    explicit LogsManager(const QString name, QObject *parent = 0);
    void setFilePath(const QString path);
    void writeWord(unsigned int word);
    void writeTime(double time);
    void writeSizeBuf(unsigned int size);
    void openFile();
    void closeFile();
    void read(int adress);
    int sizeBuffer()const;
    FileReader *reader;
    QString path;
    ~LogsManager();
signals:

public slots:
    void applyBuffer();
};

#endif // LOGSMANAGER_H
