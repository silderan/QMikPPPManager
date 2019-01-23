#ifndef QPPPLOGER_H
#define QPPPLOGER_H

#include <qstring.h>
#include <QList>
#include <QObject>
#include <QTimer>

#include "QSecretData.h"
#include "ROSData/ROSSecret.h"

class QPPPLogger : public QObject
{
Q_OBJECT

	QString m_logDir;	// Directorio donde se guardarà el registro.
	QString m_appUserName;	// Usuario que está usando el programa.
	QMap<QString, QString> m_logMap;
	QTimer flushTimer;

	QString currentFName(const QString &pre) const;
	QString currentGlobalFName() const;
	QString currentUserFName() const;

	void flush(QMap<QString, QString> &m_registros, const QString &logFName);
	void startFlushing();
	void addPPPLog(QString text);
	void logIfChanges(const QString &pppUserName, const QString &oldValue, const QString &newValue, const QString &field);

public:
	QPPPLogger(QObject *papi = Q_NULLPTR);
	~QPPPLogger();
	void setUserName(const QString &appUserName) { m_appUserName = appUserName;	}

public slots:
	void flush();
	void shutdown();

	void setLogDir(const QString &logDir) { m_logDir = logDir;	}
	const QString &logDir() const { return m_logDir;	}

	void logAddingSecret(const ROSPPPSecret &pppSecret);
	void logDeletingSecret(const ROSPPPSecret &pppSecret);
	void logChangingSecret(const ROSPPPSecret &oldSecret, const ROSPPPSecret &newSecret);
};

extern QPPPLogger logService;

#endif // QPPPLOGER_H
