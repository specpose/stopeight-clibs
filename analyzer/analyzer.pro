QMAKE_CXXFLAGS += -std=c++11
TEMPLATE = lib
TARGET = stopeight-clibs-analyzer

CONFIG += console
CONFIG -= lib_bundle
CONFIG -= qt

DEFINES += ANALYZER_LIBRARY

SOURCES += src/test.cpp

HEADERS += include/test.h\
           include/analyzer_global.h
