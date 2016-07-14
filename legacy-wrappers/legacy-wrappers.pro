#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T14:03:43
#
#-------------------------------------------------
QT       += gui
//QT       -= gui

TARGET = stopeight-clibs-legacy-wrappers
TEMPLATE = lib

DEFINES += LEGACYWRAPPERS_LIBRARY

win32:INCLUDEPATH += C:/Python27/include/
else:unix:INCLUDEPATH += /usr/include/python2.7/
//unix:INCLUDEPATH += /usr/include/numpy/

SOURCES += \
    interfacepython.cpp

HEADERS +=\
    interfacepython.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../legacy/build/release/ -lstopeight-clibs-legacy
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../legacy/build/debug/ -lstopeight-clibs-legacy

INCLUDEPATH += $$PWD/../legacy/include/
