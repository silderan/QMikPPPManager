#include "QPPPLogger.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>

void QPPPLogger::flush(QMap<QString, QString> &registros, const QString &logFName)
{
	if( registros.count() )
	{
		QFile f(logFName);

		if( !f.open(QIODevice::Text | QIODevice::Append) )
			addPPPLog( tr("WARNING: No se ha podido abrir el fichero %1").arg(logFName) );
		else
		{
			QTextStream out(&f);
			QMapIterator<QString, QString> it(registros);

			while( it.hasNext() )
			{
				it.next();
				out << tr("%1\t%2\t%3\n"). arg(it.value(), m_appUserName, it.key());
			}
			registros.clear();
			f.flush();
			f.close();
		}
	}
}

void QPPPLogger::flush()
{
	static bool flushing;

	if( !flushing )
	{
		flushing = true;
		flush( m_logMap, currentUserFName() );
		flushing = false;
	}
}

QString QPPPLogger::currentFName(const QString &pre) const
{
	int currentYear = QDate::currentDate().year();
	int currentMonth = QDate::currentDate().month();
	return QDir::toNativeSeparators(QString("%1/%2_%3-%4.log").arg(logDir(), pre).arg(currentMonth).arg(currentYear));
}

QString QPPPLogger::currentGlobalFName() const
{
	return currentFName(QString("Global"));
}

QString QPPPLogger::currentUserFName() const
{
	return currentFName(m_appUserName);
}

void QPPPLogger::startFlushing()
{
	if( !flushTimer.isActive() )
	{
		flushTimer.setSingleShot(true);
		flushTimer.start(1000);
	}
}

void QPPPLogger::addPPPLog(QString text)
{
	if( !m_logMap.contains(text) )
	{
		m_logMap.insert( text, QDateTime::currentDateTimeUtc().toString("dd/MM/yyyy hh:mm:ss") );
		startFlushing();
	}
}

QPPPLogger::QPPPLogger(QObject *papi) : QObject(papi)
{
	connect(&flushTimer, SIGNAL(timeout()), this, SLOT(flush()));
}

QPPPLogger::~QPPPLogger()
{
	flush();
}

void QPPPLogger::shutdown()
{
	flush();
}

void QPPPLogger::logIfChanges(const QString &pppUserName, const QString &oldValue, const QString &newValue, const QString &field)
{
	if( oldValue != newValue )
		addPPPLog( QString("%1\t%2: %3 -> %4").arg(pppUserName, field, oldValue, newValue) );
}

void QPPPLogger::logAddingSecret(const ROSPPPSecret &pppSecret)
{
	addPPPLog( tr("Nuevo usuario %1 con perfil %2").arg(pppSecret.userName(), pppSecret.originalProfile()) );
}

void QPPPLogger::logDeletingSecret(const ROSPPPSecret &pppSecret)
{
	addPPPLog( tr("Borra al usuario %1 (%2) con perfil %3").arg(pppSecret.userName(), ServiceState::readableString(pppSecret.serviceState()), pppSecret.originalProfile()) );
}

void QPPPLogger::logChangingSecret(const ROSPPPSecret &oldSecret, const ROSPPPSecret &newSecret)
{
	const QString &pppUserName = oldSecret.userName();

	logIfChanges( pppUserName, oldSecret.userName(), newSecret.userName(), tr("Nombre usuario PPP") );
	logIfChanges( pppUserName, oldSecret.userPass(), newSecret.userPass(), tr("Contraseña usuario PPP") );
	logIfChanges( pppUserName, ServiceState::readableString(oldSecret.serviceState()), ServiceState::readableString(newSecret.serviceState()), tr("Estado Servicio") );
	logIfChanges( pppUserName, oldSecret.originalProfile(), newSecret.originalProfile(), tr("Perfil") );
}

QPPPLogger logService;
