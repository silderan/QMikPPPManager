#ifndef QREGISTRO_H
#define QREGISTRO_H

#include <qstring.h>
#include <QList>
#include <QSecretData.h>
#include <QObject>
#include <QTimer>

struct QRegData
{
	QDateTime m_fecha;
	QString m_tipo;
	QString m_who;
	QString m_action;
	QSecretData m_sd;

	QRegData(QDateTime fecha, const QString &who, const QSecretData &sd, const QString &action) :
		m_fecha(fecha),
		m_who(who),
		m_action(action),
		m_sd(sd)
	{	}
};

class QRegistro : public QObject
{
Q_OBJECT
	QString m_logDir;	// Directorio donde se guardarà el registro.
	QString m_uname;	// Usuario que está usando el programa.
	QList<QRegData> m_registrosGlobales;
	QList<QRegData> m_registrosUsuario;
	QTimer flushTimer;

	QString currentFName(const QString &pre) const;
	QString currentGlobalFName() const;
	QString currentUserFName() const;

	void flush(QList<QRegData> &m_registros, const QString &logFName);
	void startFlushing();

public:
	QRegistro(QObject *papi = Q_NULLPTR);
	~QRegistro();
	void setUserName(const QString &uname) { m_uname = uname;	}
	void shutdown();

	void registraCambio( const QSecretData &secretOld, const QString &texto);
	void registraCambio(const QSecretData &secretOld, const QString &viejo, const QString &nuevo, const QString &campo, const QString &formato = "%1 ha cambiado de '%2' a '%3'" );
	void registraCambios( const QSecretData &secretOld, const QSecretData &secretNew );

public slots:
	void setLogDir(const QString &logDir) { m_logDir = logDir;	}
	const QString &logDir() const { return m_logDir;	}
	void addRegistro(const QSecretData &sd, const QString &action);
	void flush();
};

extern QRegistro logService;

#endif // QREGISTRO_H
