/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QPPPLOGER_H
#define QPPPLOGER_H

#include <QString>
#include <QDir>
#include <QList>
#include <QObject>
#include <QTimer>

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
	void flush(QPPPLogDataList &pppLogDataList, const QString &logFName);
	void startFlushing();
	void addPPPLog(const PPPLogData &pppLogData);
	void logIfChanges(const QString &pppUserName, const QString &field, const QString &oldValue, const QString &newValue);

	QStringList allLogFiles() const;
	void readLogs(const QString &logFName, const QString &userName, QPPPLogDataList &pppLogdataList);

public:
	QPPPLogger(QObject *papi = Q_NULLPTR);
	~QPPPLogger();

	QString currentGlobalFName() const;
	QString currentUserFName() const;
	QString currentCompactFName() const;

	void setUserName(const QString &appUserName) { m_appUserName = appUserName;	}
	int logsReaded() const	{ return m_logsReaded;	}
	int filesReaded() const	{ return m_filesReaded;	}
	qint64 msReading()const { return m_msReading;	}
	bool compactAllFiles();
	int removeOldFiles();

public slots:
	void flush();
	void shutdown();

	void setLogDir(const QString &logDir) { m_logDir = QDir::toNativeSeparators(logDir);	}
	const QString &logDir() const { return m_logDir;	}

	void logAddingSecret(const ROSPPPSecret &pppSecret);
	void logDeletingSecret(const ROSPPPSecret &pppSecret);
	void logChangingSecret(const ROSPPPSecret &oldSecret, const ROSPPPSecret &newSecret);
	QPPPLogDataList readLogs(const QString &userName = QString());
};

extern QPPPLogger logService;

#endif // QPPPLOGER_H
