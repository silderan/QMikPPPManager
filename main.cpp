#include "QMikPPPManager.h"
#include <QApplication>

#include "Utils/QRegistro.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMikPPPManager w;
	logService.setLogDir(qApp->applicationDirPath());
	w.show();
	return a.exec();
}
