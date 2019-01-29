#include "QPPPLogger.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QElapsedTimer>

void QPPPLogger::readLogs(const QString &logFName, const QString &userName, QPPPLogDataList &pppLogdataList)
{
	QFile f(logFName);

	if( !f.open(QIODevice::Text | QIODevice::ReadOnly) )
		qDebug( tr("WARNING: No se ha podido abrir el fichero %1").arg(logFName).toLatin1().constData() );
	else
	{
		QStringList lineBits;
		PPPLogData pppLogData;
		m_filesReaded++;

		while( !f.atEnd() )
		{
			m_logsReaded++;
			QByteArray line = f.readLine();
			if( line.at(line.count()-1) == '\n' )
				line.resize(line.count()-1);
			lineBits = QString().fromLatin1(line.trimmed()).split('\t');
			if( lineBits.count() >= 4 )
			{
				pppLogData.timestamp = lineBits[0];
				pppLogData.appUserName = lineBits[1];
				pppLogData.pppUserName = lineBits[2];

				if( lineBits.count() == 6 )
				{
					pppLogData.field = lineBits[3];
					pppLogData.oldValue = lineBits[4];
					pppLogData.newValue = lineBits[5];
				}
				else
				{
					if( lineBits[3] == "baja" )
					{
						pppLogData.field = tr("Estado servicio");
						pppLogData.oldValue = "Activo";
						pppLogData.newValue = "Cancelado";
					}
					else
					if( lineBits[3] == "ALTA" )
					{
						pppLogData.field = tr("Estado servicio");
						pppLogData.oldValue = "Cancelado";
						pppLogData.newValue = "Activo";
					}
					else
					if( lineBits[3].startsWith("Creado nuevo usuario con perfil ") )
					{
						pppLogData.field = tr("Nuevo usuario");
						pppLogData.oldValue = "Activo indefinido";
						pppLogData.newValue = lineBits[3].mid(32);
					}
					else
					{
						QRegExp reg( "([\\w á-ú]*) ha cambiado de '([^']*)' a '([^']*)'" );
						if( reg.indexIn(lineBits[3]) > -1 )
						{
							if( reg.cap().count() > 1) pppLogData.field = reg.cap(1);
							if( reg.cap().count() > 2) pppLogData.oldValue = reg.cap(2);
							if( reg.cap().count() > 3) pppLogData.newValue = reg.cap(3);
						}
						else
						{
							pppLogData.field = "FailParse";
							pppLogData.oldValue = "";
							pppLogData.newValue = reg.cap(0);
						}
					}
				}
				if( userName.isEmpty() || (pppLogData.pppUserName == userName) ||
						// This weird comparations are necessary for users where the userName changed over time.
						(pppLogData.oldValue == userName) || (pppLogData.newValue == userName) )
					if( !pppLogdataList.contains(pppLogData) )
						pppLogdataList.append( pppLogData  );
			}
		}
		f.close();
	}
}

void QPPPLogger::flush(QPPPLogDataList &pppLogDataList, const QString &logFName)
{
	if( pppLogDataList.count() )
	{
		QFile f(logFName);

		if( !f.open(QIODevice::Text | QIODevice::Append) )
			qDebug( tr("WARNING: No se ha podido abrir el fichero %1").arg(logFName).toLatin1().constData() );
		else
		{
			QTextStream out(&f);
			foreach( const PPPLogData &pppLogData, pppLogDataList )
			{
				out << tr("%1\t%2\t%3\t%4\t%5\t%6\n"). arg(pppLogData.timestamp,
													   m_appUserName,
													   pppLogData.pppUserName,
													   pppLogData.field,
													   pppLogData.oldValue,
													   pppLogData.newValue);
			}
			pppLogDataList.clear();
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
		flush( m_pppLogDataList, currentUserFName() );
		flushing = false;
	}
}


QPPPLogDataList QPPPLogger::readLogs(const QString &userName)
{
	QPPPLogDataList rtn;
	QStringList files = allLogFiles();

	m_logsReaded = 0;
	m_filesReaded = 0;
	QElapsedTimer timer;
	timer.start();
	foreach( const QString &file, files )
	{
		readLogs( file, userName, rtn );
	}
	m_msReading = timer.elapsed();
	return rtn;
}

bool QPPPLogger::compactAllFiles()
{
	QPPPLogDataList logs = readLogs();
	if( logs.count() )
	{
		flush( logs, currentCompactFName() );
		return true;
	}
	return false;
}

int QPPPLogger::removeOldFiles()
{
	int rtn = 0;
	QStringList files = allLogFiles();
	QString compactFName = currentCompactFName();

	Q_ASSERT( files.contains(currentCompactFName()) );

	foreach( const QString &file, files )
	{
		if( file != compactFName )
			rtn += QFile(file).remove() ? 1 : 0;
	}

	return rtn;
}

QString QPPPLogger::currentFName(const QString &pre) const
{
	Q_ASSERT( !pre.contains(QRegExp("[\\\\\\/]")) );
	int currentYear = QDate::currentDate().year();
	int currentMonth = QDate::currentDate().month();
	return QString("%1/%2_%3-%4.log").arg(logDir(), pre).arg(currentMonth).arg(currentYear);
}

QString QPPPLogger::currentGlobalFName() const
{
	return currentFName(QString("Global"));
}

QString QPPPLogger::currentUserFName() const
{
	return currentFName(m_appUserName);
}

QString QPPPLogger::currentCompactFName() const
{
	return currentFName("Compacted");
}

void QPPPLogger::startFlushing()
{
	if( !flushTimer.isActive() )
	{
		flushTimer.setSingleShot(true);
		flushTimer.start(1000);
	}
}

void QPPPLogger::addPPPLog( const PPPLogData &pppLogData )
{
	if( !m_pppLogDataList.contains(pppLogData) )
	{
		m_pppLogDataList.append( pppLogData );
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

void QPPPLogger::logIfChanges(const QString &pppUserName, const QString &field, const QString &oldValue, const QString &newValue)
{
	if( oldValue != newValue )
		addPPPLog( PPPLogData(QDateTime::currentDateTimeUtc().toString("dd/MM/yyyy hh:mm:ss"), m_appUserName, pppUserName, field, oldValue, newValue) );
}

QStringList QPPPLogger::allLogFiles()const
{
	QStringList list = QDir( logDir()).entryList( QStringList() << "*.log", QDir::Files );

	for( int i = list.count()-1; i >= 0; --i )
		list[i] = QString( "%1/%2").arg( logDir(), list.at(i) );

	return list;
}

void QPPPLogger::logAddingSecret(const ROSPPPSecret &pppSecret)
{
	logIfChanges( pppSecret.userName(), "Nuevo Usuario", ServiceState::readableString(pppSecret.serviceState()), pppSecret.originalProfile() );
}

void QPPPLogger::logDeletingSecret(const ROSPPPSecret &pppSecret)
{
	logIfChanges( pppSecret.userName(), "Borra al usuario", ServiceState::readableString(pppSecret.serviceState()), pppSecret.originalProfile() );
}

void QPPPLogger::logChangingSecret(const ROSPPPSecret &oldSecret, const ROSPPPSecret &newSecret)
{
	const QString &pppUserName = oldSecret.userName();

	logIfChanges( pppUserName, tr("Nombre usuario PPP"), oldSecret.userName(), newSecret.userName() );
	logIfChanges( pppUserName, tr("Contraseña usuario PPP"), oldSecret.userPass(), newSecret.userPass() );
	logIfChanges( pppUserName, tr("Estado Servicio"), ServiceState::readableString(oldSecret.serviceState()), ServiceState::readableString(newSecret.serviceState()) );
	logIfChanges( pppUserName, tr("Perfil"), oldSecret.originalProfile(), newSecret.originalProfile() );
}

QPPPLogger logService;
