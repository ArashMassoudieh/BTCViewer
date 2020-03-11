#-------------------------------------------------
#
# Project created by QtCreator 2020-03-11T10:47:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BTCViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += ../qcustomplot/ \
    ../GIFMod/src/GUI

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ../qcustomplot/qcustomplot.cpp \
    ../GIFMod/src/GUI/BTC.cpp \
    ../GIFMod/src/GUI/BTCSet.cpp \
    ../GIFMod/src/GUI/Distribution.cpp \
    ../GIFMod/src/GUI/NormalDist.cpp \
    ../GIFMod/src/GUI/QuickSort.cpp \
    ../GIFMod/src/GUI/Vector.cpp \
    ../GIFMod/src/GUI/StringOP.cpp \
    ../GIFMod/src/GUI/Matrix.cpp \
    ../GIFMod/src/GUI/Matrix_arma.cpp \
    ../GIFMod/src/GUI/utility_funcs.cpp \
    ../GIFMod/src/GUI/Vector_arma.cpp \
    ../GIFMod/src/GUI/DistributionNUnif.cpp

HEADERS += \
        mainwindow.h \
        ../qcustomplot/qcustomplot.h \
    ../GIFMod/src/GUI/BTC.h \
    ../GIFMod/src/GUI/BTCSet.h \
    ../GIFMod/src/GUI/Distribution.h \
    ../GIFMod/src/GUI/NormalDist.h \
    ../GIFMod/src/GUI/QuickSort.h \
    ../GIFMod/src/GUI/Vector.h \
    ../GIFMod/src/GUI/StringOP.h \
    ../GIFMod/src/GUI/Matrix.h \
    ../GIFMod/src/GUI/Matrix_arma.h \
    ../GIFMod/src/GUI/utility_funcs.h \
    ../GIFMod/src/GUI/Vector_arma.h \
    ../GIFMod/src/GUI/DistributionNUnif.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# LAPACK — Linear Algebra PACKage lib and include locations

win32 {

    LAPACK_INCLUDE = $$PWD/include
    #64 bits build
    contains(QMAKE_TARGET.arch, x86_64) {
        #debug
        CONFIG(debug, debug|release) {
            LAPACK_LIB_DIR = $$PWD/libs/lapack-blas_lib_win64/debug
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MTd \
                    -lblas_win64_MTd
        }
        #release
        CONFIG(release, debug|release) {
            LAPACK_LIB_DIR = $$PWD/libs/lapack-blas_lib_win64/release
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MT \
                    -lblas_win64_MT
        }
    }

    INCLUDEPATH += $${LAPACK_INCLUDE}

    DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS

}

linux {
    #sudo apt-get install libblas-dev liblapack-dev
     DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS
     LIBS += -llapack -lblas -larmadillo
}
