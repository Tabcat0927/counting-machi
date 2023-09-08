QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    digitunitframe.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    setupwidget.cpp

HEADERS += \
    digitunitframe.h \
    loginwidget.h \
    mainwidget.h \
    mainwindow.h \
    setupwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

INCLUDEPATH += $$PWD/../include \
               $$PWD/../include/control \
               $$PWD/../include/item



TARGET = CountGrain

win32 : contains(QT_ARCH, X86_64){
    message("x64")
}
win32 : contains(QT_ARCH, i386){
    CONFIG(debug, debug | release){
        DESTDIR = $$PWD/../bin/debug
        OBJECTS_DIR = $$PWD/../temp/debug
        LIBS += $$PWD/../lib/debug/VisionGraph.lib
    }
    CONFIG(release, debug | release){
        DESTDIR = $$PWD/../bin/release
        OBJECTS_DIR = $$PWD/../temp/release
        LIBS += $$PWD/../lib/release/VisionGraph.lib
    }
}


