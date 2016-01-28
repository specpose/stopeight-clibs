#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T20:20:25
#
#-------------------------------------------------
QT       += gui
//QT       -= gui

TARGET = stopeight-clibs-legacy
TEMPLATE = lib

DEFINES += LEGACY_LIBRARY

//INCLUDEPATH += $$PWD/../analyzer/

SOURCES += \
    src/listcopyable.cpp \
    src/listrotator.cpp \
    src/listbase.cpp \
    src/listswitchable.cpp \
    src/dpoint.cpp \
    src/myreal.cpp \
    src/spiralscalculator.cpp \
    src/spiralsanalyzer.cpp \
    src/cliffscalculator.cpp \
    src/cliffsanalyzer.cpp \
    src/areaanalyzer.cpp \
    src/areacalculator.cpp \
    src/turnnormalizer.cpp \
    src/turncalculator.cpp \
    src/areanormalizer.cpp \
    src/cornercalculator.cpp \
    src/cornernormalizer.cpp \
    src/calculator.cpp \
    src/analyzer.cpp \
    src/editorbase.cpp \
    src/spirals.cpp \
    src/editorspirals.cpp \
    src/straightscalculator.cpp
HEADERS +=\
    include/listcopyable.h \
    include/listrotator.h \
    include/listbase.h \
    include/legacy_global.h \
    include/listswitchable.h \
    include/editorinterface.h \
    include/dpoint.h \
    include/myreal.h \
    include/spiralscalculator.h \
    include/spiralsanalyzer.h \
    include/cliffscalculator.h \
    include/cliffsanalyzer.h \
    include/areaanalyzer.h \
    include/areacalculator.h \
    include/turnnormalizer.h \
    include/turncalculator.h \
    include/areanormalizer.h \
    include/cornercalculator.h \
    include/cornernormalizer.h \
    include/calculator.h \
    include/analyzer.h \
    include/editorbase.h \
    include/spirals.h \
    include/editorspirals.h \
    include/straightscalculator.h

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
