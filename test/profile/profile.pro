CONFIG += c++17 debug
QMAKE_CXXFLAGS += -Wall -o2 -DNDEBUG

include(../../chess/chess.pri)
HEADERS += ../test_helper.h
SOURCES += ../test_helper.cpp profile.cpp 

DESTDIR = build
OBJECTS_DIR = $$DESTDIR
TARGET = profile

CONFIG += run_post_build

unix {
   TEST_CMD = "./build/profile"
   test.target = test
   test.depends = FORCE
   test.commands = $$TEST_CMD

   callgrind.target = callgrind
   callgrind.depends = FORCE
   callgrind.commands = valgrind --tool=callgrind $$TEST_CMD

   cachegrind.target = cachegrind
   cachegrind.depends = FORCE
   cachegrind.commands = valgrind --tool=cachegrind $$TEST_CMD

   regen.target = regen
   regen.depends = distclean
   regen.commands = "qmake6 && make"

   QMAKE_EXTRA_TARGETS += test regen callgrind cachegrind
}
