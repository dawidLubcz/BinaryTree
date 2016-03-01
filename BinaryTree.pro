TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += exceptions

SOURCES += main.cpp \
    cmybinarytree.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cmybinarytree.h \
    ilogger.h \
    clogger.h \
    celapsedtime.h

