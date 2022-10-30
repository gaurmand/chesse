#include <QApplication>
#include <QMainWindow>

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
   #ifdef RUN_TEST
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
   #endif

   QApplication a(argc, argv);
   QMainWindow w;
   w.setWindowTitle("chesse");
   w.show();
   return a.exec();
}
