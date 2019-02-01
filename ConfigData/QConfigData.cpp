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
	return QConfigData::setupComboBox(cb, false, select, clientProfileMap().profileNames());
}

QComboBox *QConfigData::setupCBPerfilesUsables(QComboBox *cb, const QString &select)
{
	return QConfigData::setupComboBox(cb, false, select, clientProfileMap().regularProfileNames());
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

OpenBrowserInfoList QConfigData::openBrowserInfoList()
{
	static OpenBrowserInfoList rtn;
	if( rtn.isEmpty() )
	{
		rtn.append( OpenBrowserInfo(QObject::tr("Estándar"), "http", "80", "") );
		rtn.append( OpenBrowserInfo(QObject::tr("VoIP ATA"), "http", "8080", "") );
		rtn.append( OpenBrowserInfo(QObject::tr("VoIP ATA'"), "http", "8888", "") );
		rtn.append( OpenBrowserInfo(QObject::tr("Router/AP interior"), "http", "2001", "") );
	}
	return rtn;
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
#define LKEY_COLSHIDDEN		("columns-hidden")

// Global protected data keys.
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
	m_columnsHidden.clear();
	foreach( const QString &col, cnfgData[LKEY_COLSHIDDEN].split(',', QString::SkipEmptyParts) )
		m_columnsHidden.append( col.toInt() );

	m_tableCellLook.load(cnfgData);
}

void QConfigData::loadGlobalProtectedData()
{
	QIniData cnfgData;
	QIniFile::load(m_rosProtectedFName, &cnfgData);

	m_instaladores	= cnfgData[GPKEY_INSTALADORES].split(',', QString::SkipEmptyParts);
	m_comerciales	= cnfgData[GPKEY_COMERCIALES].split(',', QString::SkipEmptyParts);

	m_clientProfileMap.load(cnfgData);
	m_staticIPv4RangeListMap.load(cnfgData);
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

	cnfgData[LKEY_COLSHIDDEN].clear();
	foreach( int col, m_columnsHidden )
		cnfgData[LKEY_COLSHIDDEN].append( QString("%1,").arg(col) );

	m_tableCellLook.save(cnfgData);
	QIniFile::save(m_userFName, cnfgData);
}

void QConfigData::saveGlobalProtectedData() const
{
	QIniData cnfgData;

	cnfgData[GPKEY_COMERCIALES]	= m_comerciales.join(',');
	cnfgData[GPKEY_INSTALADORES]= m_instaladores.join(',');

	m_clientProfileMap.save(cnfgData);
	m_staticIPv4RangeListMap.save(cnfgData);

	QIniFile::save(m_rosProtectedFName, cnfgData);
}


void QConfigData::saveGlobalData() const
{
	QIniData cnfgData;
	m_connectInfoList.save(cnfgData);
	QIniFile::save(m_rosFName, cnfgData);
}
