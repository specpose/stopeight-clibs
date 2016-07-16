#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T14:03:43
#
#-------------------------------------------------
CONFIG -= qt

win32:TARGET = stopeight_clibs_analyzer
else:unix:TARGET = stopeight-clibs-analyzer-wrappers
TEMPLATE = lib
//win32:QMAKE_LFLAGS_SONAME = .pyd
DEFINES += ANALYZERWRAPPERS_LIBRARY

win32:LIBS += -LC:/Python27/libs
win32:INCLUDEPATH += C:/Python27/include
else:unix:INCLUDEPATH += /usr/include/python2.7/
//unix:INCLUDEPATH += /usr/include/numpy/

SOURCES += \
    interfacepython.cpp

HEADERS +=\
    interfacepython.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer/release/ -lstopeight-clibs-analyzer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer/release/ -lstopeight-clibs-analyzer
unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer/build/release/ -lstopeight-clibs-analyzer
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer/build/release/ -lstopeight-clibs-analyzer

INCLUDEPATH += $$PWD/../analyzer/include/
