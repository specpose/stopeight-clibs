QMAKE_CXXFLAGS += -std=c++1y
TEMPLATE = lib
TARGET = stopeight-clibs-analyzer
win32:CONFIG+= staticlib

CONFIG -= lib_bundle
CONFIG -= qt

DEFINES += ANALYZER_LIBRARY

win32:INCLUDEPATH += $$PWD/../../triSYCL/include/
else:unix:INCLUDEPATH += $$PWD/../../triSYCL/include/

SOURCES += src/test.cpp \
    src/main.cpp

HEADERS += include/test.h\
           include/analyzer_global.h
