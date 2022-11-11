CONFIG += c++17 debug
QMAKE_CXXFLAGS += -Wall -o1 -DNDEBUG

include(../chess/chess.pri)
HEADERS += ../test/test_helper.h
SOURCES += ../test/test_helper.cpp profile.cpp 

DESTDIR = build
OBJECTS_DIR = $$DESTDIR
TARGET = profile

CONFIG += run_post_build

unix {
   TEST_CMD = "./build/profile"
   test.target = test
   test.depends = FORCE
   test.commands = $$TEST_CMD

   profile.target = profile
   profile.depends = FORCE
   profile.commands = valgrind --tool=callgrind $$TEST_CMD

   regen.target = regen
   regen.depends = distclean
   regen.commands = "qmake6 && make"

   QMAKE_EXTRA_TARGETS += test regen profile
}
