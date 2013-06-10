#-------------------------------------------------
#
# Project created by QtCreator 2013-06-11T00:10:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AvisOmatiCQt
TEMPLATE = app


SOURCES +=\
    src/VehicleContainer.cpp \
    src/Vehicle.cpp \
    src/Rent.cpp \
    src/Motorcycle.cpp \
    src/main.cpp \
    src/Date.cpp \
    src/CopyContainer.cpp \
    src/Copy.cpp \
    src/Car.cpp \
    src/BorrowerContainer.cpp \
    src/Borrower.cpp \
    src/Address.cpp \
    src/mainwindow.cpp

HEADERS  += \
    include/VehicleContainer.h \
    include/Vehicle.h \
    include/Rent.h \
    include/Motorcycle.h \
    include/Date.h \
    include/CopyContainer.h \
    include/Copy.h \
    include/Car.h \
    include/BorrowerContainer.h \
    include/Borrower.h \
    include/Address.h \
    include/mainwindow.h

FORMS    += mainwindow.ui
