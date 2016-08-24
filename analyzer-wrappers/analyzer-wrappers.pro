#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T14:03:43
#
#-------------------------------------------------
QMAKE_CXXFLAGS += -std=c++1y

TEMPLATE = lib
win32:TARGET = stopeight_clibs_analyzer
else:unix:TARGET = stopeight-clibs-analyzer-wrappers
CONFIG -= lib_bundle
CONFIG -= qt

DEFINES += ANALYZERWRAPPERS_LIBRARY

win32:LIBS += -LC:/Python35/libs
win32:INCLUDEPATH += C:/Python35/include
else:unix:INCLUDEPATH += /usr/include/python3.5/

SOURCES += \
    interfacepython.cpp

HEADERS +=\
    interfacepython.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer/stopeight-clibs-analyzer/Release/ -lstopeight-clibs-analyzer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer/stopeight-clibs-analyzer/Debug/ -lstopeight-clibs-analyzer
unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer/build/release/ -lstopeight-clibs-analyzer
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer/build/debug/ -lstopeight-clibs-analyzer

INCLUDEPATH += $$PWD/../analyzer/include/
