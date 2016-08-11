#include "QRegistro.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>

void QRegistro::addRegistro(const QSecretData &sd, const QString &action)
{
	m_registrosGlobales.append(QRegData(QDateTime::currentDateTimeUtc(), m_uname, sd, action));
	m_registrosUsuario.append(QRegData(QDateTime::currentDateTimeUtc(), m_uname, sd, action));
	startFlushing();
}

void QRegistro::flush(QList<QRegData> &registros, const QString &logFName)
{
	if( registros.count() )
	{
		QFile f(logFName);

		if( !f.open(QIODevice::Text | QIODevice::Append) )
			addRegistro(QSecretData(), tr("WARNING: No se ha podido abrir el fichero %1").arg(logFName));
		else
		{
			QTextStream out(&f);
			for( int i = 0; i < registros.count(); i++ )
			{
				out << tr("%1\t%2\t%3\t%4\n").
					   arg(registros[i].m_fecha.toString("dd/MM/yyyy hh:mm:ss"),
						   registros[i].m_who,
						   registros[i].m_sd.usuario(),
						   registros[i].m_action);
			}
			registros.clear();
			f.flush();
			f.close();
		}
	}
}

void QRegistro::flush()
{
	static bool flushing;

	if( !flushing )
	{
		flushing = true;
		flush(m_registrosGlobales, currentGlobalFName());
		flush(m_registrosUsuario, currentUserFName());
		flushing = false;
	}
}

QString QRegistro::currentFName(const QString &pre) const
{
	int currentYear = QDate::currentDate().year();
	int currentMonth = QDate::currentDate().month();
	return QDir::toNativeSeparators(QString("%1/%2_%3-%4.log").arg(logDir(), pre).arg(currentMonth).arg(currentYear));
}

QString QRegistro::currentGlobalFName() const
{
	return currentFName(QString("Global"));
}

QString QRegistro::currentUserFName() const
{
	return currentFName(m_uname);
}

void QRegistro::startFlushing()
{
	if( !flushTimer.isActive() )
	{
		flushTimer.setSingleShot(true);
		flushTimer.start(1000);
	}
}

QRegistro::QRegistro(QObject *papi) : QObject(papi)
{
	connect(&flushTimer, SIGNAL(timeout()), this, SLOT(flush()));
}

QRegistro::~QRegistro()
{
	flush();
}

void QRegistro::shutdown()
{
	flush();
	if( m_registrosGlobales.count() || m_registrosUsuario.count() )
	{
		throw tr("No han podido escribir registros en el fichero: %1 globales y %2 de usuario").arg(m_registrosGlobales.count()).arg(m_registrosUsuario.count());
	}
}

void QRegistro::registraCambios(const QSecretData &secretOld, const QSecretData &secretNew)
{
	if( secretOld.dadoDeBaja() != secretNew.dadoDeBaja() )
	{
		if( secretNew.dadoDeBaja() )
			registraCambio(secretOld, "baja");
		else
			registraCambio(secretOld, "ALTA");
	}
	registraCambio( secretOld, secretOld.codigoCliente(), secretNew.codigoCliente(), "El código de cliente" );
	registraCambio( secretOld, secretOld.usuario(), secretNew.usuario(), "El usuario" );
	registraCambio( secretOld, secretOld.contra(), secretNew.contra(), "La contraseña PPPoE" );
	registraCambio( secretOld, secretOld.perfilOriginal(), secretNew.perfilOriginal(), "El perfil" );
	registraCambio( secretOld, secretOld.nombre(), secretNew.nombre(), "El nombre" );
	registraCambio( secretOld, secretOld.direccion(), secretNew.direccion(), "La dirección" );
	registraCambio( secretOld, secretOld.telefonos(), secretNew.telefonos(), "El teléfono" );
	registraCambio( secretOld, secretOld.poblacion(), secretNew.poblacion(), "La población" );
	registraCambio( secretOld, secretOld.instalador(), secretNew.instalador(), "El instalador" );
	registraCambio( secretOld, secretOld.comercial(), secretNew.comercial(), "El comercial" );
	registraCambio( secretOld, secretOld.email(), secretNew.email(), "El Email" );
	registraCambio( secretOld, secretOld.wPass(), secretNew.wPass(), "La contraseña WiFi" );
	registraCambio( secretOld, secretOld.SSID(), secretNew.SSID(), "La SSID" );
	registraCambio( secretOld, secretOld.notas(), secretNew.notas(), "Las notas" );
}

void QRegistro::registraCambio(const QSecretData &secretOld, const QString &texto)
{
	addRegistro(secretOld, texto);
}

void QRegistro::registraCambio(const QSecretData &secretOld, const QString &viejo, const QString &nuevo, const QString &campo, const QString &formato)
{
	if( viejo != nuevo )
		registraCambio(secretOld, QString(formato).arg(campo, viejo, nuevo));
}

QRegistro logService;
