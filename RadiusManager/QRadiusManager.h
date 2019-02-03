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

#ifndef QRADIUSMANAGER_H
#define QRADIUSMANAGER_H

#define USE_RADIUS

#ifdef USE_RADIUS

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "../ConfigData/ConnectInfo.h"
#include "../Utils/Utils.h"

#include "../ROSData/ROSSecret.h"

class QRadiusManager
{
	ConnectInfo m_connInfo;
	QSqlDatabase m_db;
	QString m_dataBaseName;
	QString m_usersTableName;
	QMap<QString, QString> m_usersTableData;

public:
	QRadiusManager();

	void setConnInfo( const ConnectInfo &connInfo, const QString &dataBaseName )
	{
		m_connInfo = connInfo;
		m_dataBaseName = dataBaseName;
	}
	QString name() const		{ return m_connInfo.routerName();	}
	bool isConnected() const	{ return m_db.isOpen();				}
	bool open();
	void close();
	QString lastErrorString()const	{ return m_db.lastError().text();	}
	bool updateRemoteData(const ROSDataBase &rosData);
};

#endif

#endif // QRADIUSMANAGER_H
