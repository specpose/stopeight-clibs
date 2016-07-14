#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T14:03:43
#
#-------------------------------------------------
CONFIG -= qt

TARGET = stopeight-clibs-analyzer-wrappers
TEMPLATE = lib

DEFINES += ANALYZERWRAPPERS_LIBRARY

win32:INCLUDEPATH += C:/Python27/include/
else:unix:INCLUDEPATH += /usr/include/python2.7/
//unix:INCLUDEPATH += /usr/include/numpy/

SOURCES += \
    interfacepython.cpp

HEADERS +=\
    interfacepython.h

CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer/build/release/ -lstopeight-clibs-analyzer
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer/build/debug/ -lstopeight-clibs-analyzer

INCLUDEPATH += $$PWD/../analyzer/include/
