QT       += core gui
QT       += serialport
QT       += widgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4):

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
    gaugewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    process_message.cpp \
    qcustomplot.cpp \
    sensorerrordelegate.cpp \
    sensorerrortable.cpp \
    settingsdialog.cpp

HEADERS += \
    gaugewidget.h \
    mainwindow.h \
    process_message.h \
    qcustomplot.h \
    sensorerrordelegate.h \
    sensorerrortable.h \
    settingsdialog.h

FORMS += \
    mainwindow.ui \
    sensorerrortable.ui \
    settingsdialog.ui

include(FlatTabWidget/FlatTabWidget.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/Aircraft control panel wallpaper.jpg \
    img/Aircraft control panel wallpaper.png \
    img/Aircraft control panel wallpaper.png \
    img/Aircraft control panel wallpaper.png \
    img/Aircraft control panel wallpaper.png

RESOURCES += \
    resources.qrc

