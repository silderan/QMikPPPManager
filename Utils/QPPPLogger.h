#ifndef QPPPLOGER_H
#define QPPPLOGER_H

#include <qstring.h>
#include <QList>
#include <QObject>
#include <QTimer>
#include "QSecretData.h"
#include "ROSData/ROSSecret.h"

struct PPPLogData
{
	QString timestamp;
	QString appUserName;
	QString pppUserName;
	QString field;
	QString oldValue;
	QString newValue;
	bool operator==(const PPPLogData &other)
	{
		return  (newValue == other.newValue) &&
				(oldValue == other.oldValue) &&
				(pppUserName == other.pppUserName) &&
				(field == other.field) &&
				(appUserName == other.appUserName) &&
				(timestamp == other.timestamp);
	}
	PPPLogData()
	{	}
	PPPLogData(const QString &timestamp, const QString &appUserName, const QString &pppUserName, const QString &field, const QString &oldValue, const QString &newValue)
		: timestamp(timestamp)
		, appUserName(appUserName)
		, pppUserName(pppUserName)
		, field(field)
		, oldValue(oldValue)
		, newValue(newValue)
	{

	}
};

typedef QList<PPPLogData> QPPPLogDataList;

class QPPPLogger : public QObject
{
Q_OBJECT

	QString m_logDir;		// Directorio donde se guardarà el registro.
	QString m_appUserName;	// Usuario que está usando el programa.
	QPPPLogDataList m_pppLogDataList;
	QTimer flushTimer;
	int m_logsReaded;
	int m_filesReaded;
	qint64 m_msReading;

	QString currentFName(const QString &pre) const;
	QString currentGlobalFName() const;
	QString currentUserFName() const;

	void flush(QPPPLogDataList &pppLogDataList, const QString &logFName);
	void startFlushing();
	void addPPPLog(const PPPLogData &pppLogData);
	void logIfChanges(const QString &pppUserName, const QString &field, const QString &oldValue, const QString &newValue);

	void readLogs(const QString &logFName, const QString &userName, QPPPLogDataList &pppLogdataList);

public:
	QPPPLogger(QObject *papi = Q_NULLPTR);
	~QPPPLogger();
	void setUserName(const QString &appUserName) { m_appUserName = appUserName;	}
	int logsReaded() const	{ return m_logsReaded;	}
	int filesReaded() const	{ return m_filesReaded;	}
	qint64 msReading()const { return m_msReading;	}

public slots:
	void flush();
	void shutdown();

	void setLogDir(const QString &logDir) { m_logDir = logDir;	}
	const QString &logDir() const { return m_logDir;	}

	void logAddingSecret(const ROSPPPSecret &pppSecret);
	void logDeletingSecret(const ROSPPPSecret &pppSecret);
	void logChangingSecret(const ROSPPPSecret &oldSecret, const ROSPPPSecret &newSecret);
	QPPPLogDataList readLogs(const QString &userName = QString());
};

extern QPPPLogger logService;

#endif // QPPPLOGER_H
