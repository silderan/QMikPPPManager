#include "QMikPPPManager.h"
#include <QApplication>

#include <QRegularExpressionMatch>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMikPPPManager w;
	w.show();

	return a.exec();
}
