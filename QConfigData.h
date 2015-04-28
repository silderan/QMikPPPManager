#ifndef QCONFIGDATA_H
#define QCONFIGDATA_H
#include "QIniFile.h"
#include "QSentences.h"

#include <QComboBox>
#include <QStringList>
#include <QDir>

#define IPV4_TO_UINT(_A, _B, _C, _D)	((quint32)(((((quint8)_A)&255)<<24)+((((quint8)_B)&255)<<16)+((((quint8)_C)&255)<<8)+(((quint8)_D)&255)))
#define UINT_TO_IPV4A(_IPV4_)			((((quint32)_IPV4_)>>24)&255)
#define UINT_TO_IPV4B(_IPV4_)			((((quint32)_IPV4_)>>16)&255)
#define UINT_TO_IPV4C(_IPV4_)			((((quint32)_IPV4_)>>8)&255)
#define UINT_TO_IPV4D(_IPV4_)			(((quint32)_IPV4_)&255)
#define UINT_TO_SIPV4(_IPV4_)			(QString("%1.%2.%3.%4").arg(UINT_TO_IPV4A(_IPV4_)).arg(UINT_TO_IPV4B(_IPV4_)).arg(UINT_TO_IPV4C(_IPV4_)).arg(UINT_TO_IPV4D(_IPV4_)))

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
public:
	enum NivelUsuario
	{
		SinPermisos,			// No puede hacer nada.
		Instalador,				// No puede modificar perfiles ni desactivar cuentas.
		Manager,				// No puede modificar nombres de usuario.
		Administrador			// Puede hacerlo todo.
	};

private:
	QString m_userFName;
	QString m_rosFName;
	QPerfilesList m_perfiles;			// Los perfiles no se guardarán.
	QIniData m_userData;				// Información de configuración del usuario.
	QIniData m_rosData;					// Información de configuración del ROS.
	NivelUsuario m_nivelUsuario;

public:
	static const QString tagSecret;
	static const QString tagLSecret;
	static const QString tagPerfil;
	static const QString tagActivo;
	static const QString tagLActivo;
	static const QString tagNuevo;
	static const QString tagAPIUser;

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
		setNivelUsuario(SinPermisos);
	}

	QConfigData() : m_userFName(QDir::homePath()+"/PPPManagerUser.ini"), m_rosFName("PPPManagerROS.ini")
	{
		defaults();
	}
	~QConfigData()
	{
	}
	void load() { QIniFile::load(m_userFName, &m_userData); QIniFile::load(m_rosFName, &m_rosData); }
	void save() const;

	void setRemoteHost(const QString &host) { m_userData["RemoteHost"] = host; }
	QString remoteHost() const { return m_userData["RemoteHost"]; }

	void setRemotePort(const quint16 &port) { m_userData["RemotePort"] = QString("%1").arg(port); }
	quint16 remotePort() const { return m_userData["RemotePort"].toUShort(); }

	void setUserName(const QString &uname) { m_userData["UserName"] = uname;	}
	QString userName() const { return m_userData["UserName"]; }

	void setUserPass(const QString &upass) { m_userData["UserPass"] = upass;	}
	QString userPass() const { return m_userData["UserPass"]; }

	void setPerfilInactivo(const QString &p) { m_rosData["PerfilInactivo"] = p; }
	QString perfilInactivo() const { return m_rosData["PerfilInactivo"]; }

	void setPerfilBasico(const QString &p) { m_rosData["PerfilBasico"] = p; }
	QString perfilBasico() const { return m_rosData["PerfilBasico"]; }

	QPerfilesList &perfiles() { return m_perfiles; }
	void addPerfil(const ROS::QSentence &s) { m_perfiles.append(s); }

	QStringList perfilesUsables() const			{ return m_rosData["PerfilesUsables"].split(',');	}
	void setPerfilesUsables(const QStringList &pp)	{ m_rosData["PerfilesUsables"] = pp.join(',');		}

	void setTamFuente(int s) { m_userData["TamFuente"] = QString("%1").arg(s); }
	int tamFuente() const { return m_userData["TamFuente"].toInt(); }

	void setAlturaLinea(int s) { m_userData["AlturaLinea"] = QString("%1").arg(s); }
	int alturaLinea() const { return m_userData["AlturaLinea"].toInt(); }

	void setDeIPV4(quint32 ip) { m_rosData["DeIPV4"] = QString("%1").arg(ip); }
	void setDeIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setDeIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 deIPV4() const { return m_rosData["DeIPV4"].toUInt(); }
	void setAIPV4(quint32 ip) { m_rosData["AIPV4"] = QString("%1").arg(ip); }
	void setAIPV4(quint8 A, quint8 B, quint8 C, quint8 D) { setAIPV4(IPV4_TO_UINT(A, B, C, D)); }
	quint32 aIPV4() const { return m_rosData["AIPV4"].toUInt(); }
	static quint32 toVIPV4(const QString &sip);
	bool esIPEstatica(const QString &sip) const;
	bool esIPEstatica(quint32 vip) const;

	void setInstaladores(const QStringList &l) { m_rosData["Instaladores"] = l.join(","); }
	QStringList instaladores() const { return m_rosData["Instaladores"].split(",", QString::SkipEmptyParts); }

	void setComerciales(const QStringList &l) { m_rosData["Comerciales"] = l.join(","); }
	QStringList comerciales(bool soloComerciales) const { return m_rosData["Comerciales"].split(",", QString::SkipEmptyParts) + (soloComerciales ? QStringList() : instaladores()); }

	static void select(QComboBox *cb, const QString &str);
	static QComboBox *setupComboBox(QComboBox *cb, bool editable, const QString &select, const QStringList &s);
	QComboBox *setupCBPerfiles(QComboBox *cb, const QString &select);
	QComboBox *setupCBPerfilesUsables(QComboBox *cb, const QString &select);
	QComboBox *setupCBInstaladores(QComboBox *cb, const QString &select);
	QComboBox *setupCBVendedores(QComboBox *cb, const QString &select);
	QComboBox *setupCBIPsPublicas(QComboBox *cb, const QStringList &ipsUsadas, const QString &ipActual = QString());
	QComboBox *setupCBPoblaciones(QComboBox *cb, const QStringList &poblaciones, const QString &poblacion = QString());
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
	QConfigData::NivelUsuario nivelUsuario() const { return m_nivelUsuario; }
	void setNivelUsuario(const QConfigData::NivelUsuario &n) { m_nivelUsuario = n; }
};

extern QConfigData gGlobalConfig;

#endif // QCONFIGDATA_H
