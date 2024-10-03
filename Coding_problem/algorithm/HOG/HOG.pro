TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

PARTYDIR = $$_PRO_FILE_PWD_/../lib

INCLUDEPATH += $$PARTYDIR/opencv/include
OpenCV_Lib = $$PARTYDIR/opencv/lib

LIBS += $$OpenCV_Lib/* \

OPENCVDIR = $$PARTYDIR/opencv/bin
OPENCVDIR ~= s,/,\\,g

ZLIBDIR = $$PARTYDIR/zlib/bin
ZLIBDIR ~= s,/,\\,g

LZ4DIR = $$PARTYDIR/lz4/bin
LZ4DIR ~= s,/,\\,g

LIBWEBPDIR = $$PARTYDIR/libwebp/bin
LIBWEBPDIR ~= s,/,\\,g

DLLDIR = $$_PRO_FILE_PWD_/release
DLLDIR ~= s,/,\\,g

QMAKE_POST_LINK += \
        $$quote(xcopy /Y /S /I $${OPENCVDIR}\\* $$DLLDIR $$escape_expand(\\n\\t)) \
        $$quote(xcopy /Y /S /I $${ZLIBDIR}\\* $$DLLDIR $$escape_expand(\\n\\t)) \
        $$quote(xcopy /Y /S /I $${LZ4DIR}\\* $$DLLDIR $$escape_expand(\\n\\t)) \
        $$quote(xcopy /Y /S /I $${LIBWEBPDIR}\\* $$DLLDIR $$escape_expand(\\n\\t)) \

SOURCES += \
        main.cpp
