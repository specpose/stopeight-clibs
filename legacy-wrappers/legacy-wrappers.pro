#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T14:03:43
#
#-------------------------------------------------
QT       += gui

TEMPLATE = lib
win32:TARGET = stopeight_clibs_legacy
else:unix:TARGET = stopeight-clibs-legacy-wrappers
CONFIG -= lib_bundle
CONFIG += qt

DEFINES += LEGACYWRAPPERS_LIBRARY

win32:LIBS += -LC:/Python27/libs
win32:INCLUDEPATH += C:/Python27/include
else:unix:INCLUDEPATH += /usr/include/python2.7/

SOURCES += interfacepython.cpp

HEADERS += interfacepython.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../legacy/release/ -lstopeight-clibs-legacy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../legacy/debug/ -lstopeight-clibs-legacy
unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../legacy/build/release/ -lstopeight-clibs-legacy
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../legacy/build/debug/ -lstopeight-clibs-legacy

INCLUDEPATH += $$PWD/../legacy/include/
