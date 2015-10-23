#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T20:20:25
#
#-------------------------------------------------
QT       -= gui

TARGET = legacy
TEMPLATE = lib

DEFINES += LEGACY_LIBRARY

INCLUDEPATH += $$PWD/../analyzer/

SOURCES += \
    listbase.cpp \
    dpoint.cpp

HEADERS +=\
        legacy_global.h \
    listbase.h \
    dpoint.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE93DCC36
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = legacy.dll
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
