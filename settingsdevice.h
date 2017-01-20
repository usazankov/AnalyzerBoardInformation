#ifndef SETTINGSDEVICE_H
#define SETTINGSDEVICE_H
#include <QList>
#include <typeinfo>
namespace dev {
    enum TypeDevice{NullDevice,ArincDevice};
}
struct ConfParametr;
class SettingsDevice{
public:
    explicit SettingsDevice();
    QString name;
    virtual dev::TypeDevice typeSettings()const;
    virtual ~SettingsDevice();
};

class SettingsArincDevice:public SettingsDevice
{
public:
    explicit SettingsArincDevice();
    QList<ConfParametr*>* confParametrs();
    void setConfParametrs(const QList<ConfParametr *> &p);

    int getTimeStepToUpdateData() const;
    void setTimeStepToUpdateData(int value);

    int getTimeStepToWriteFile() const;
    void setTimeStepToWriteFile(int value);

    int getTimeStepToUpdateGraphs() const;
    void setTimeStepToUpdateGraphs(int value);

    bool getIsRestructData() const;
    void setIsRestructData(bool value);

    int getTimeStepToUpdateTable() const;
    void setTimeStepToUpdateTable(int value);

    bool getLoadDataFromFile() const;
    void setLoadDataFromFile(bool value);

    double getReducedStep() const;
    void setReducedStep(double value);

    int getTimeStepToReduce() const;
    void setTimeStepToReduce(int value);

private:
    QList<ConfParametr*> params;
    int timeStepToUpdateData;//в миллисекундах
    int timeStepToUpdateTable;//в миллисекундах
    int timeStepToWriteFile;//в миллисекундах
    int timeStepToUpdateGraphs;//в миллисекундах
    double reducedStep;//в секундах
    int timeStepToReduce;//в секундах
    bool loadDataFromFile;
    bool restructData;
};
#endif // SETTINGSDEVICE_H
