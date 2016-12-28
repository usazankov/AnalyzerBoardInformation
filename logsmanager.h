#ifndef LOGSMANAGER_H
#define LOGSMANAGER_H

#include <QObject>

class LogsManager : public QObject
{
    Q_OBJECT
public:
    explicit LogsManager(QObject *parent = 0);

signals:

public slots:
};

#endif // LOGSMANAGER_H