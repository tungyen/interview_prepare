TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bresenham.cpp \
        convexhull.cpp \
        main.cpp \
        polygon.cpp

HEADERS += \
    bresenham.h \
    convexhull.h \
    polygon.h
