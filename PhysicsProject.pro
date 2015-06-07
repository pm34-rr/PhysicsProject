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
    src/Calculations.cpp

HEADERS += src/mainwindow.h \
           src/cscene3d.h \
           src/caction.h \
           src/cmodel.h \
           src/main.h \
           src/Storage.h \
           src/WorkDock.h \
    src/Calculations.h

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

