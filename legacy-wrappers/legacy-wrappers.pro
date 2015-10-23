#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T14:03:43
#
#-------------------------------------------------
QT       -= gui

TARGET = legacy-wrappers
TEMPLATE = lib

DEFINES += LEGACYWRAPPERS_LIBRARY

INCLUDEPATH += $$PWD/../legacy/
INCLUDEPATH += /usr/include/python2.7/
//INCLUDEPATH += /usr/include/numpy/

SOURCES += legacywrappers.cpp

HEADERS += legacywrappers.h\
        legacy-wrappers_global.h \
    interfacepython.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE4FFC43E
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = legacy-wrappers.dll
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
