CONFIG += c++17 debug
QMAKE_CXXFLAGS += -Wall

include(gui/gui.pri)
include(chess/chess.pri)
include(test/test.pri)

DESTDIR = build
OBJECTS_DIR = $$DESTDIR
TARGET = chesse

DEFINES += RUN_APP
#DEFINES += RUN_TEST
CONFIG += run_post_build

unix {
   TEST_CMD = "./build/chesse"
   test.target = test
   test.depends = FORCE
   test.commands = $$TEST_CMD

   rebuild.target = rebuild
   rebuild.depends = clean all

   regen.target = regen
   regen.depends = distclean
   regen.commands = "qmake6 && make"

   QMAKE_EXTRA_TARGETS += test rebuild regen

   run_post_build {
      QMAKE_POST_LINK += $$TEST_CMD
   }
}
