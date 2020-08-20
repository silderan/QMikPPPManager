#include "QMikPPPManager.h"
#include <QApplication>

//struct PortData
//{
//	QString ip;
//	QString protocolo;
//	QString lanFirstPort;
//	QString lanLastPort;
//	QString wanFirstPort;
//	QString wanLastPort;
//	QString name;
//};

//#include <QDebug>
//void testTemplateFileName()
//{
//	QFile file("D:/Projects/QMikPPPManager/build-QMikPPPManager-Desktop_Qt_5_15_0_MinGW_32_bit-Debug/templates/ONT_EK_4AC_Panoramica.romfile.cfg");
//	if( file.open(QIODevice::ReadOnly) )
//	{
//		QString str = QString::fromLatin1(file.readAll());
//		QStringList list;
//		int pos = 0;

//		QRegExp rx("\\{\\{([^:]+)\\:([^:]+)\\:([^:]*)\\}\\}");
//		for( pos = 0; (pos = rx.indexIn(str, pos)) != -1; pos += rx.matchedLength() )
//		{
//			qDebug() << rx.cap(1);
//			qDebug() << rx.captureCount();
//		}
//	}
//}

#include "Utils/QPPPLogger.h"
int main(int argc, char *argv[])
{
//	testTemplateFileName();
	QApplication a(argc, argv);
	QMikPPPManager w;
	logService.setLogDir(qApp->applicationDirPath());
	w.show();
	return a.exec();
}
