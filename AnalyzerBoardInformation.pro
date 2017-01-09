#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T14:40:29
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnalyzerBoardInformation
TEMPLATE = app


SOURCES += main.cpp\
    arincreader.cpp \
    maincontroller.cpp \
    logsmanager.cpp \
    ArincBoards/arincboardmpc429linux.cpp \
    ArincBoards/arincboardpci429linux.cpp \
    UnpackingArinc/arincparametr.cpp \
    UnpackingArinc/dataarinc32.cpp \
    UnpackingArinc/parametr.cpp \
    UnpackingArinc/states.cpp \
    FormsModels/formadddevice.cpp \
    FormsModels/formconfparamsdevice.cpp \
    FormsModels/formdecparam.cpp \
    FormsModels/formdiscrparam.cpp \
    FormsModels/mainview.cpp \
    FormsModels/mdiform.cpp \
    FormsModels/mdiformdiscr.cpp \
    FormsModels/modelconfparams.cpp \
    FormsModels/qlabelhasword.cpp \
    arincdevice.cpp \
    device.cpp \
    settingsdevice.cpp

HEADERS  += \
    arincmodelinterface.h \
    arincparametrobserver.h \
    arincreader.h \
    maincontroller.h \
    logsmanager.h \
    ArincBoards/arincboardmpc429linux.h \
    ArincBoards/arincboardpci429linux.h \
    ArincBoards/pci429LNX.h \
    ArincBoards/arincintefaces.h \
    UnpackingArinc/arincparametr.h \
    UnpackingArinc/dataarinc32.h \
    UnpackingArinc/databehavior.h \
    UnpackingArinc/parametr.h \
    UnpackingArinc/parametr_impl.h \
    UnpackingArinc/states.h \
    FormsModels/formadddevice.h \
    FormsModels/formconfparamsdevice.h \
    FormsModels/formdecparam.h \
    FormsModels/formdiscrparam.h \
    FormsModels/mainview.h \
    FormsModels/mdiform.h \
    FormsModels/mdiformdiscr.h \
    FormsModels/modelconfparams.h \
    FormsModels/qlabelhasword.h \
    settingsdevice.h \
    arincdevice.h \
    device.h

FORMS    += \
    FormsModels/formadddevice.ui \
    FormsModels/formconfparamsdevice.ui \
    FormsModels/formdecparam.ui \
    FormsModels/mainview.ui \
    FormsModels/mdiform.ui \
    FormsModels/mdiformdiscr.ui \
    FormsModels/formdiscrparam.ui


RESOURCES += \
    rsc.qrc \
    style.qrc

DISTFILES +=
