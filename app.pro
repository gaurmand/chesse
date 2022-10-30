QT += core gui widgets
CONFIG += c++17 debug
SOURCES += main.cpp
DESTDIR = build
OBJECTS_DIR = $$DESTDIR
MAKEFILE = makefile
TARGET = app

unix {
   QMAKE_POST_LINK = "./build/app"
}
