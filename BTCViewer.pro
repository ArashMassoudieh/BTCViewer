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

GIFMod_Path = E:/Gifmod

CONFIG += c++11

INCLUDEPATH += ../qcustomplot/ \
    $${GIFMod_Path}/src/GUI

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ../qcustomplot/qcustomplot.cpp \
    $${GIFMod_Path}/src/GUI/BTC.cpp \
    $${GIFMod_Path}/src/GUI/BTCSet.cpp \
    $${GIFMod_Path}/src/GUI/Distribution.cpp \
    $${GIFMod_Path}/src/GUI/NormalDist.cpp \
    $${GIFMod_Path}/src/GUI/QuickSort.cpp \
    $${GIFMod_Path}/src/GUI/Vector.cpp \
    $${GIFMod_Path}/src/GUI/StringOP.cpp \
    $${GIFMod_Path}/src/GUI/Matrix.cpp \
    $${GIFMod_Path}/src/GUI/Matrix_arma.cpp \
    $${GIFMod_Path}/src/GUI/utility_funcs.cpp \
    $${GIFMod_Path}/src/GUI/Vector_arma.cpp \
    $${GIFMod_Path}/src/GUI/DistributionNUnif.cpp

HEADERS += \
        mainwindow.h \
        ../qcustomplot/qcustomplot.h \
    $${GIFMod_Path}/src/GUI/BTC.h \
    $${GIFMod_Path}/src/GUI/BTCSet.h \
    $${GIFMod_Path}/src/GUI/Distribution.h \
    $${GIFMod_Path}/src/GUI/NormalDist.h \
    $${GIFMod_Path}/src/GUI/QuickSort.h \
    $${GIFMod_Path}/src/GUI/Vector.h \
    $${GIFMod_Path}/src/GUI/StringOP.h \
    $${GIFMod_Path}/src/GUI/Matrix.h \
    $${GIFMod_Path}/src/GUI/Matrix_arma.h \
    $${GIFMod_Path}/src/GUI/utility_funcs.h \
    $${GIFMod_Path}/src/GUI/Vector_arma.h \
    $${GIFMod_Path}/src/GUI/DistributionNUnif.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# LAPACK — Linear Algebra PACKage lib and include locations

win32 {

    LAPACK_INCLUDE = $${GIFMod_Path}/include
    message($$LAPACK_INCLUDE)
    #64 bits build
    contains(QMAKE_TARGET.arch, x86_64) {
        #debug
        CONFIG(debug, debug|release) {
            LAPACK_LIB_DIR = $${GIFMod_Path}/libs/lapack-blas_lib_win64/debug
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MTd \
                    -lblas_win64_MTd
        }
        #release
        CONFIG(release, debug|release) {
            LAPACK_LIB_DIR = $${GIFMod_Path}/libs/lapack-blas_lib_win64/release
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MT \
                    -lblas_win64_MT
        }
    }

    INCLUDEPATH += $${LAPACK_INCLUDE}
    message ($$INCLUDEPATH)
    DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS

}

linux {
    #sudo apt-get install libblas-dev liblapack-dev
     DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS
     LIBS += -llapack -lblas -larmadillo
}
