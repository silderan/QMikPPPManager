#ifndef QCONFIGDATA_H
#define QCONFIGDATA_H

#include <QComboBox>
#include <QStringList>
#include <QDir>
#include <QColor>

#include "../Utils/IPv4Range.h"
#include "../Utils/QIniFile.h"
#include "../ROSAPI/QSentences.h"
#include "ConnectInfo.h"
#include "ClientProfile.h"
#include "TableCellLook.h"

class QConfigData
{
public:
	// El órden es importante porque en un sitio se controla qué puede editar cada uno y
	// se hace una comparación por el valor.
	enum NivelUsuario
	{
		SinPermisos,			// No puede hacer nada.
		Comercial,				// No puede modificar nada.
		Instalador,				// No puede modificar perfiles ni desactivar cuentas.
		Administrador,			// No puede modificar la configuración del programa.
		Supervisor				// Puede hacerlo todo.
	};

private:
	QString m_userName;
	QString m_userPass;

	QString m_userFName;
	QString m_rosFName;
	QString m_rosProtectedFName;

	QClientProfileList m_perfiles;			// Los perfiles no se guardarán.

	QStringList m_instaladores;			// Lista de nombres instaladores.
	QStringList m_comerciales;			// Lista de nombres de los comerciales/vendedores.
	NivelUsuario m_nivelUsuario;
	IPv4RangeMap m_staticIPv4Map;		// Lista de rangos de IP estáticas.

	QString m_exportFile;				// Fichero al que se exporta.

	QConnectInfoList m_connectInfoList;

	bool m_pantallaMaximizada;
	int m_anchoPantalla;
	int m_altoPantalla;

	// Apariencia de las tablas
	TableCellLook m_tableCellLook;

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
		addRange( IPv4Range(IPv4(192,168,1,50), IPv4(192,168,1,254)) );
		setNivelUsuario(SinPermisos);
	}

#ifdef QT_DEBUG
	QConfigData() : m_userFName(QDir::homePath()+"/PPPManagerUserDebug.ini"), m_rosFName("PPPManagerROSDebug.ini"), m_rosProtectedFName("PPPManagerROSProtectedDebug.ini")
#else
	QConfigData() : m_userFName(QDir::homePath()+"/PPPManagerUser.ini"), m_rosFName("PPPManagerROS.ini"), m_rosProtectedFName("PPPManagerROSProtected.ini")
#endif
	{
		defaults();
	}
	~QConfigData()
	{
	}
	void loadLocalUserData();
	void loadGlobalData();
	void loadGlobalProtectedData();
	void saveLocalUserData() const;
	void saveGlobalProtectedData() const;
	void saveGlobalData() const;

	QConnectInfoList &connectInfoList() { return   m_connectInfoList;	}

	void setExportFile(const QString &exportFile) { m_exportFile = exportFile;	}
	QString exportFile() const { return m_exportFile; }

	const QString &userName() const				{ return m_userName;	}
	void setUserName(const QString &userName)	{ m_userName = userName;}

	const QString &userPass() const				{ return m_userPass;	}
	void setUserPass(const QString &userPass)	{ m_userPass = userPass;}

	bool isWindowMaximized() const					{ return m_pantallaMaximizada;		}
	void setWindowMaximized(bool maximizada = true)	{ m_pantallaMaximizada = maximizada;}

	int anchoPantalla() const			{ return m_anchoPantalla;	}
	int altoPantalla() const			{ return m_altoPantalla;	}

	void setAnchoPantalla(int a)		{ m_anchoPantalla = a;	}
	void setAltoPantalla(int a)			{ m_altoPantalla = a;	}

	QClientProfileList &perfiles()					{ return m_perfiles;	}
	void addPerfil(const ROS::QSentence &s)			{ m_perfiles.append(s); }

	void addRange(const IPv4Range &ipv4Range)		{ m_staticIPv4Map.addRange(ipv4Range);			}
	void delRange(const QString &ipv4RangeName)		{ m_staticIPv4Map.delRange(ipv4RangeName);		}
	void delRange(const IPv4Range &ipv4Range)		{ m_staticIPv4Map.delRange(ipv4Range.name());	}

	bool esIPEstatica(const IPv4 &ipv4) const		{ return m_staticIPv4Map.inRange(ipv4);	}

	void setInstaladores(const QStringList &l)		{ m_instaladores = l;	}
	void addInstalador(const QString &instalador)	{ if( !m_instaladores.contains(instalador) ) m_instaladores.append(instalador); }
	const QStringList &instaladores() const			{ return m_instaladores;}

	void setComerciales(const QStringList &l)		{ m_comerciales = l;	}
	void addComercial(const QString &instalador)	{ if( !m_comerciales.contains(instalador) ) m_comerciales.append(instalador); }
	const QStringList &comerciales() const			{ return m_comerciales; }

	const IPv4RangeMap &staticIPv4Map() const		{ return m_staticIPv4Map;	}

	TableCellLook &tableCellLook()					{ return m_tableCellLook;	}

	static void select(QComboBox *cb, const QString &str);
	static QComboBox *setupComboBox(QComboBox *cb, bool editable, const QString &select, const QStringList &s);
	QComboBox *setupCBPerfiles(QComboBox *cb, const QString &select);
	QComboBox *setupCBPerfilesUsables(QComboBox *cb, const QString &select);
	QComboBox *setupCBInstaladores(QComboBox *cb, const QString &select);
	QComboBox *setupCBVendedores(QComboBox *cb, const QString &select);

	QComboBox *setupCBPoblaciones(QComboBox *cb, const QStringList &poblaciones, const QString &poblacion = QString());

	QConfigData::NivelUsuario nivelUsuario() const { return m_nivelUsuario; }
	void setNivelUsuario(const QConfigData::NivelUsuario &n) { m_nivelUsuario = n; }
};

extern QConfigData gGlobalConfig;

#endif // QCONFIGDATA_H
