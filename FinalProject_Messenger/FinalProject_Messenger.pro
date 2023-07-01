QT       += core gui
QT       += network
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channel.cpp \
    contact.cpp \
    dialog_login.cpp \
    dialog_logout.cpp \
    dialog_signup.cpp \
    group.cpp \
    main.cpp \
    mainwindow.cpp \
    startwindow.cpp \
    user.cpp

HEADERS += \
    channel.h \
    contact.h \
    dialog_login.h \
    dialog_logout.h \
    dialog_signup.h \
    group.h \
    mainwindow.h \
    startwindow.h \
    user.h

FORMS += \
    dialog_login.ui \
    dialog_logout.ui \
    dialog_signup.ui \
    mainwindow.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
