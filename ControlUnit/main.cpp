#include "ControlUnit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ControlUnit w;
	w.show();
	return a.exec();
}
