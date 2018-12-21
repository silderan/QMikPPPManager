#include "QConfigData.h"

const QString QConfigData::tagSecret	= "Secret";
const QString QConfigData::tagLSecret	= "LSecret";
const QString QConfigData::tagPerfil	= "Perfil";
const QString QConfigData::tagActivo	= "Activo";
const QString QConfigData::tagLActivo	= "LACtivo";
const QString QConfigData::tagNuevo		= "Nuevo";
const QString QConfigData::tagAPIUser	= "APIUser";

QConfigData gGlobalConfig;

QComboBox *QConfigData::setupCBPerfiles(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, perfiles().profileNames());
}

QComboBox *QConfigData::setupCBPerfilesUsables(QComboBox *cb, const QString &select)
{
	QStringList pp = perfiles().profileNames();
	QString p;
	foreach(p, pp)
		if( esPerfilInterno(p) )
			pp.removeOne(p);
	return QConfigData::setupComboBox(cb, false, select, pp);
}

QComboBox *QConfigData::setupCBInstaladores(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, QStringList() << "no-definido" << instaladores() );
}

QComboBox *QConfigData::setupCBVendedores(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, true, select, comerciales()+instaladores() );
}

QComboBox *QConfigData::setupCBPoblaciones(QComboBox *cb, const QStringList &poblaciones, const QString &poblacion)
{
	return setupComboBox(cb, true, poblacion, poblaciones);
}

void QConfigData::select(QComboBox *cb, const QString &str)
{
	int i = cb->findText(str);
	if( i != -1 )
		cb->setCurrentIndex(i);
	else
		cb->setCurrentText(str);
}

QComboBox *QConfigData::setupComboBox(QComboBox *cb, bool editable, const QString &select, const QStringList &items)
{
	cb->setEditable(editable);
	cb->addItems(items);
	QConfigData::select(cb, select);
	return cb;
}

// Local user data keys.
#define LKEY_USERNAME		("user-name")
#define LKEY_USERPASS		("user-password")
#define LKEY_EXPORT_FILE	("export-file")
#define LKEY_ANCHO_PANTALLA	("ancho-pantalla")
#define LKEY_ALTO_PANTALLA	("alto-pantalla")
#define LKEY_MAXIMIZADA		("pantalla-maximmizada")
#define LKEY_TAM_FUENTE		("tam-fuente-tabla")
#define LKEY_ALTO_FILA		("altura-fila-tabla")

// Global protected data keys.
#define GPKEY_PROFILE_NO_SERVICE	("perfil-clientes-de-baja")
#define GPKEY_PROFILES_UNUSABLES	("perfiles-no-usables")
#define GPKEY_PROFILE_BASIC			("perfil-basico")
#define GPKEY_COMERCIALES			("comerciales")
#define GPKEY_INSTALADORES			("instaladores")

void QConfigData::loadLocalUserData()
{
	QIniData cnfgData;
	QIniFile::load(m_userFName, &cnfgData);

	m_userName = cnfgData[LKEY_USERNAME];
	m_userPass = cnfgData[LKEY_USERPASS];

	m_exportFile = cnfgData[LKEY_EXPORT_FILE];

	m_anchoPantalla			= cnfgData[LKEY_ANCHO_PANTALLA].toInt();
	m_altoPantalla			= cnfgData[LKEY_ALTO_PANTALLA].toInt();
	m_pantallaMaximizada	= cnfgData[LKEY_MAXIMIZADA] == "true";

	m_tamFuente = cnfgData[LKEY_TAM_FUENTE].toInt();
	m_altoFilas = cnfgData[LKEY_ALTO_FILA].toInt();
}

void QConfigData::loadGlobalProtectedData()
{
	QIniData cnfgData;
	QIniFile::load(m_rosProtectedFName, &cnfgData);

	m_profileNoService	= cnfgData[GPKEY_PROFILE_NO_SERVICE];
	m_profilesUnusables	= cnfgData[GPKEY_PROFILES_UNUSABLES].split(',', QString::SkipEmptyParts);
	m_profileBasic		= cnfgData[GPKEY_PROFILE_BASIC];
	m_comerciales		= cnfgData[GPKEY_COMERCIALES].split(',', QString::SkipEmptyParts);

	m_staticIPv4Map.load(cnfgData);
}

void QConfigData::loadGlobalData()
{
	QIniData cnfgData;
	QIniFile::load(m_rosFName, &cnfgData);
	m_connectInfoList.load(cnfgData);
}

void QConfigData::saveLocalUserData() const
{
	QIniData cnfgData;

	cnfgData[LKEY_USERNAME]	= m_userName;
	cnfgData[LKEY_USERPASS]	= m_userPass;

	cnfgData[LKEY_EXPORT_FILE] = m_exportFile;

	cnfgData[LKEY_ANCHO_PANTALLA] = QString::number(m_anchoPantalla);
	cnfgData[LKEY_ALTO_PANTALLA] = QString::number(m_altoPantalla);
	cnfgData[LKEY_MAXIMIZADA] = m_pantallaMaximizada ? "true" : "false";

	cnfgData[LKEY_TAM_FUENTE] = QString::number(m_tamFuente);
	cnfgData[LKEY_ALTO_FILA] = QString::number(m_altoFilas);

	QIniFile::save(m_userFName, cnfgData);
}

void QConfigData::saveGlobalProtectedData() const
{
	if( nivelUsuario() == Supervisor )
	{
		QIniData cnfgData;

		cnfgData[GPKEY_PROFILE_NO_SERVICE]	= m_profileNoService;
		cnfgData[GPKEY_PROFILES_UNUSABLES]	= m_profilesUnusables.join(',');
		cnfgData[GPKEY_PROFILE_BASIC]		= m_profileBasic;
		cnfgData[GPKEY_COMERCIALES]			= m_comerciales.join(',');
		cnfgData[GPKEY_INSTALADORES]			= m_instaladores.join(',');

		m_staticIPv4Map.save(cnfgData);

		QIniFile::save(m_rosProtectedFName, cnfgData);
	}
}

void QConfigData::saveGlobalData() const
{
	QIniData cnfgData;
	m_connectInfoList.save(cnfgData);
	QIniFile::save(m_rosFName, cnfgData);
}
