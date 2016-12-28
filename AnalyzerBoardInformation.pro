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
    arincparametr.cpp \
    dataarinc32.cpp \
    parametr.cpp \
    states.cpp \
    arincboardmpc429linux.cpp \
    arincboardpci429linux.cpp \
    controllerarinc.cpp \
    arincreader.cpp \
    mainview.cpp \
    mdiform.cpp \
    maincontroller.cpp \
    formadddevice.cpp \
    formconfparamsdevice.cpp \
    modelconfparams.cpp \
    formdecparam.cpp \
    formdiscrparam.cpp \
    device.cpp \
    mdiformdiscr.cpp \
    logsmanager.cpp

HEADERS  += \
    arincparametr.h \
    dataarinc32.h \
    databehavior.h \
    parametr_impl.h \
    parametr.h \
    states.h \
    arincboardmpc429linux.h \
    arincboardpci429linux.h \
    arincmodelinterface.h \
    arincparametrobserver.h \
    controllerarinc.h \
    controllerinterface.h \
    pci429LNX.h \
    readingbuffer.h \
    arincreader.h \
    mainview.h \
    mdiform.h \
    maincontroller.h \
    formadddevice.h \
    formconfparamsdevice.h \
    modelconfparams.h \
    formdecparam.h \
    formdiscrparam.h \
    device.h \
    mdiformdiscr.h \
    logsmanager.h

FORMS    += \
    mainview.ui \
    mdiform.ui \
    formadddevice.ui \
    formconfparamsdevice.ui \
    formdecparam.ui \
    formdiscrparam.ui \
    mdiformdiscr.ui

RESOURCES += \
    rsc.qrc \
    style.qrc

DISTFILES +=
