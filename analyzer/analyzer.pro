#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T10:26:58
#
#-------------------------------------------------
QMAKE_CC = gcc-4.7
QMAKE_CXX = g++-4.7
QMAKE_CXXFLAGS += -std=c++11

QT       -= core gui
CONFIG += console
CONFIG -= qt

TARGET = analyzer
TEMPLATE = lib

DEFINES += ANALYZER_LIBRARY

SOURCES += analyzer.cpp

HEADERS += analyzer.h\
        analyzer_global.h \
    windowshack.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEA732C43
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = analyzer.dll
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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../legacy-build/release/ -llegacy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../legacy-build/debug/ -llegacy
else:symbian: LIBS += -llegacy
else:unix: LIBS += -L$$PWD/../legacy-build/ -llegacy

INCLUDEPATH += $$PWD/../legacy-build
DEPENDPATH += $$PWD/../legacy-build
