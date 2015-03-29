#include "QMikPPPManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMikPPPManager w;
	w.show();

	return a.exec();
}
