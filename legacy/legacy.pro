#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T20:20:25
#
#-------------------------------------------------
QT       -= gui

TARGET = stopeight-clibs-legacy
TEMPLATE = lib

DEFINES += LEGACY_LIBRARY

//INCLUDEPATH += $$PWD/../analyzer/

SOURCES += \
    src/listiteration.cpp \
    src/listrotator.cpp \
    src/listbase.cpp \
    src/listinitializer.cpp \
    src/dpoint.cpp \
    src/myreal.cpp \
    src/spiralscalculator.cpp

HEADERS +=\
    include/listiteration.h \
    include/listrotator.h \
    include/listbase.h \
    include/legacy_global.h \
    include/listinitializer.h \
    include/editorinterface.h \
    include/dpoint.h \
    include/myreal.h \
    include/spiralscalculator.h

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

//win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../analyzer-build/release/ -lanalyzer
//else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../analyzer-build/debug/ -lanalyzer
//else:symbian: LIBS += -lanalyzer
//else:unix: LIBS += -L$$PWD/../analyzer-build/ -lanalyzer

//INCLUDEPATH += $$PWD/../analyzer-build
//DEPENDPATH += $$PWD/../analyzer-build
