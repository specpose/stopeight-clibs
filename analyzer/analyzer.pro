QMAKE_CXXFLAGS += -std=c++1y
TEMPLATE = lib
TARGET = stopeight-clibs-analyzer
win32:CONFIG+= staticlib

CONFIG -= lib_bundle
CONFIG -= qt

DEFINES += ANALYZER_LIBRARY

win32:INCLUDEPATH += C:/boost_1_61_0/
win32:INCLUDEPATH += $$PWD/../../triSYCL/include/
else:unix:INCLUDEPATH += $$PWD/../../triSYCL/include/

SOURCES += src/test.cpp\
           src/Matrix.cpp\
           src/single_task.cpp

HEADERS += include/test.h\
           include/error.h\
           include/Matrix.h\
           include/single_task.h\
           include/analyzer_global.h
