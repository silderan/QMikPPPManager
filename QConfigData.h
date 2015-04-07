#ifndef QCONFIGDATA_H
#define QCONFIGDATA_H
#include "QIniFile.h"
#include "QSentences.h"

#include <QStringList>

#define IPV4_TO_UINT(_A, _B, _C, _D)	((quint32)(((((quint8)_A)&255)<<24)+((((quint8)_B)&255)<<16)+((((quint8)_C)&255)<<8)+(((quint8)_D)&255)))
#define UINT_TO_IPV4A(_IPV4_)			((((quint32)_IPV4_)>>24)&255)
#define UINT_TO_IPV4B(_IPV4_)			((((quint32)_IPV4_)>>16)&255)
#define UINT_TO_IPV4C(_IPV4_)			((((quint32)_IPV4_)>>8)&255)
#define UINT_TO_IPV4D(_IPV4_)			(((quint32)_IPV4_)&255)
#define UINT_TO_IPV4(_IPV4_)			(QString("%1.%2.%3.%4").arg(UINT_TO_IPV4A(_IPV4_)).arg(UINT_TO_IPV4B(_IPV4_)).arg(UINT_TO_IPV4C(_IPV4_)).arg(UINT_TO_IPV4D(_IPV4_)))

class QPerfilData
{
	QString m_nombre;

public:
	const QString &nombre() const { return m_nombre; }
	void setNombre(const QString &n) { m_nombre = n; }
	QPerfilData(const ROS::QSentence &s)
	{
		m_nombre = s.attribute("name");
	}
	bool operator==(const QString &nombre) const
	{
		return m_nombre == nombre;
	}
};

class QPerfilesList : public QList<QPerfilData>
{
	QStringList m_nombres;

public:
	void append(const QPerfilData &s);
	bool contains(const QString &s) const;
	const QStringList &nombres()const { return m_nombres; }
};

class QConfigData
{
	QString m_configFName;
	QPerfilesList m_perfiles;			// Los perfiles no se guardarán.
	QIniData m_iniData;

public:
	void defaults()
	{
		setRemoteHost("192.168.1.1");
		setRemotePort(8728);
		setUserName("admin");
		setUserPass("");
		setPerfilInactivo("SinAcceso");
		setPerfilBasico("5/1");
		setTamFuente(10);
		setAlturaLinea(17);
		setDeIPV4(192,168,1,50);
		setAIPV4(192,168,1,254);
	}

	QConfigData() : m_configFName("config.ini")
	{
		defaults();
	}
	~QConfigData()
	{
		save();
	}
	void load() { QIniFile::load(m_configFName, &m_iniData); }
	void save() const { QIniFile::save(m_configFName, m_iniData); }

	void setRemoteHost(const QString &host) { m_iniData["RemoteHost"] = host; }
	QString remoteHost() const { return m_iniData["RemoteHost"]; }

	void setRemotePort(const quint16 &port) { m_iniData["RemotePort"] = QString("%1").arg(port); }
	quint16 remotePort() const { return m_iniData["RemotePort"].toUShort(); }

	void setUserName(const QString &uname) { m_iniData["UserName"] = uname;	}
	QString userName() const { return m_iniData["UserName"]; }

	void setUserPass(const QString &upass) { m_iniData["UserPass"] = upass;	}
	QString userPass() const { return m_iniData["UserPass"]; }

	void setPerfilInactivo(const QString &p) { m_iniData["PerfilInactivo"] = p; }
	QString perfilInactivo() const { return m_iniData["PerfilInactivo"]; }

	void setPerfilBasico(const QString &p) { m_iniData["PerfilBasico"] = p; }
	QString perfilBasico() const { return m_iniData["PerfilBasico"]; }

	QPerfilesList &perfiles() { return m_perfiles; }
	void addPerfil(const ROS::QSentence &s) { m_perfiles.append(s); }

	void setTamFuente(int s) { m_iniData["TamFuente"] = QString("%1").arg(s); }
	int tamFuente() const { return m_iniData["TamFuente"].toInt(); }

	void setAlturaLinea(int s) { m_iniData["AlturaLinea"] = QString("%1").arg(s); }
	int alturaLinea() const { return m_iniData["AlturaLinea"].toInt(); }

	void setDeIPV4(quint32 ip) { m_iniData["DeIPV4"] = QString("%1").arg(ip); }
	void setDeIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setDeIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 deIPV4() const { return m_iniData["DeIPV4"].toUInt(); }
	void setAIPV4(quint32 ip) { m_iniData["AIPV4"] = QString("%1").arg(ip); }
	void setAIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setAIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 aIPV4() const { return m_iniData["AIPV4"].toUInt(); }

	void setInstaladores(const QStringList &l) { m_iniData["Instaladores"] = l.join(","); }
	QStringList instaladores() const { return m_iniData["Instaladores"].split(","); }
	void addInstalador(const QString &i)
	{
		if( m_iniData["Instaladores"].contains(i) )
		{
			QStringList ins = instaladores();
			ins.append(i);
			setInstaladores(ins);
		}
	}
//	void setPoblaciones(const QStringList &l) { m_iniData["Poblaciones"] = l.join(","); }
//	QStringList poblaciones() const { return m_iniData["Poblaciones"].split(","); }
//	void addPoblacion(const QString &p)
//	{
//		if( !m_iniData["Poblaciones"].contains(p) )
//		{
//			QStringList pob = poblaciones();
//			pob.append(p);
//			setPoblaciones(pob);
//		}
//	}
};

extern QConfigData gGlobalConfig;

#endif // QCONFIGDATA_H
