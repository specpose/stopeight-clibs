#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T14:10:32
#
#-------------------------------------------------
QMAKE_CC = gcc-4.7
QMAKE_CXX = g++-4.7
QMAKE_CXXFLAGS += -std=c++11

QT       -= core gui
CONFIG += console
CONFIG -= qt

TARGET = analyzer-wrappers
TEMPLATE = lib

DEFINES += ANALYZERWRAPPERS_LIBRARY

INCLUDEPATH += $$PWD/../analyzer/
INCLUDEPATH += /usr/include/python2.7/
//INCLUDEPATH += /usr/include/numpy/

SOURCES += analyzerwrappers.cpp

HEADERS += analyzerwrappers.h\
        analyzer-wrappers_global.h \
    windowshack2.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEC40E797
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = analyzer-wrappers.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer-build/release/ -lanalyzer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer-build/debug/ -lanalyzer
else:symbian: LIBS += -lanalyzer
else:unix: LIBS += -L$$PWD/../analyzer-build/ -lanalyzer

INCLUDEPATH += $$PWD/../analyzer-build
DEPENDPATH += $$PWD/../analyzer-build
