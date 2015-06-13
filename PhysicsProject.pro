#-------------------------------------------------
#
# Project created by QtCreator 2012-02-18T15:41:09
#
#-------------------------------------------------

# === Настраиваемые опции ======================================================

# Использовать высокополигональные модели
#CONFIG += use_hipoly

# ==============================================================================

DEFINES += VERSION_NUMBER=\\\"v0.39\\\"

TARGET = VLR
TEMPLATE = app

INCLUDEPATH += src

QMAKE_CXXFLAGS += -std=c++11

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += HAVE_QT5
    contains(QT_CONFIG, dynamicgl) {
        win32-g++* {
            QMAKE_LIBS += -lopengl32
        } else {
            QMAKE_LIBS += opengl32.lib
        }
        DEFINES += USE_FORCE_GL
    } else {
        contains(QT_CONFIG, opengles.) | contains(QT_CONFIG, angle) {
            error("This program requires Qt to be configured with -opengl desktop (recommended) or -opengl dynamic")
        }
    }
}

win32:lessThan(QT_VERSION, 4.5.0) {
    win32-g++*|win32-msvc|win32-msvc.net|win32-msvc200* {
        DEFINES += HAVE_OLD_QT
    }
}

SOURCES += src/main.cpp \
           src/mainwindow.cpp \
           src/cscene3d.cpp \
           src/caction.cpp \
           src/cmodel.cpp \
           src/cmilkshapemodel.cpp \
           src/Storage.cpp \
           src/WorkDock.cpp \
    src/Calculations.cpp \
    src/MathLib/alglibinternal.cpp \
    src/MathLib/alglibmisc.cpp \
    src/MathLib/ap.cpp \
    src/MathLib/dataanalysis.cpp \
    src/MathLib/diffequations.cpp \
    src/MathLib/fasttransforms.cpp \
    src/MathLib/integration.cpp \
    src/MathLib/interpolation.cpp \
    src/MathLib/linalg.cpp \
    src/MathLib/optimization.cpp \
    src/MathLib/solvers.cpp \
    src/MathLib/specialfunctions.cpp \
    src/MathLib/statistics.cpp \
    src/AppMenu.cpp \
    src/Plot.cpp

HEADERS += src/mainwindow.h \
           src/cscene3d.h \
           src/caction.h \
           src/cmodel.h \
           src/main.h \
           src/Storage.h \
           src/WorkDock.h \
    src/Calculations.h \
    src/MathLib/alglibinternal.h \
    src/MathLib/alglibmisc.h \
    src/MathLib/ap.h \
    src/MathLib/dataanalysis.h \
    src/MathLib/diffequations.h \
    src/MathLib/fasttransforms.h \
    src/MathLib/integration.h \
    src/MathLib/interpolation.h \
    src/MathLib/linalg.h \
    src/MathLib/optimization.h \
    src/MathLib/solvers.h \
    src/MathLib/specialfunctions.h \
    src/MathLib/statistics.h \
    src/MathLib/stdafx.h \
    src/AppMenu.h \
    src/Plot.h

FORMS   += \
           src/mainwindow.ui

win32 {
  RESOURCES += src/resources/manual/win32/manual.qrc
  RC_FILE += src/resources/icon.rc
}

RESOURCES += src/resources/mres.qrc \
             src/resources/help/help.qrc \
             src/resources/menuicons/menuicons.qrc \
             src/resources/models/m_cyllinder.qrc \
    src/resources/models/lowpoly/m_wall_left.qrc \
    src/resources/models/lowpoly/m_wall_right.qrc

use_hipoly {
  RESOURCES +=
}
else {
  RESOURCES += src/resources/models/lowpoly/m_mass.qrc \
               src/resources/models/lowpoly/m_spring_end.qrc \
               src/resources/models/lowpoly/m_spring_start.qrc \
               src/resources/models/lowpoly/t_black_metall.qrc \
               src/resources/models/lowpoly/t_dk_gray_metall.qrc \
               src/resources/models/lowpoly/t_lt_gray_metall.qrc
}

# === Сборочные директории =====================================================

DESTDIR = .
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

# === Опции компиляции =========================================================

QMAKE_RESOURCE_FLAGS += -threshold 0 -compress 9
CONFIG += warn_on

*g++*|*clang* {
    QMAKE_CXXFLAGS_WARN_ON *= -Wextra
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
    QMAKE_CXXFLAGS_RELEASE *= -ffast-math
    QMAKE_CXXFLAGS_RELEASE *= -fno-math-errno
}

*msvc* {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -Ox
    DEFINES += _CRT_SECURE_NO_WARNINGS
    DEFINES += _USE_MATH_DEFINES
}

