#include "guicontrolunit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  GuiControlUnit w;
  w.show();

  return a.exec();
}
