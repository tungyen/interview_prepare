TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        convexhull.cpp \
        main.cpp \
        polygon.cpp

HEADERS += \
    convexhull.h \
    polygon.h
