#include "QMikPPPManager.h"
#include <QApplication>

struct PortData
{
	QString ip;
	QString protocolo;
	QString lanFirstPort;
	QString lanLastPort;
	QString wanFirstPort;
	QString wanLastPort;
	QString name;
};


#include "Utils/QPPPLogger.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMikPPPManager w;
	logService.setLogDir(qApp->applicationDirPath());
	w.show();
	return a.exec();
}
