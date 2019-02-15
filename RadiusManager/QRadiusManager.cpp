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

#include "QRadiusManager.h"

#ifdef USE_RADIUS

QRadiusManager::QRadiusManager()
	: m_usersTableName("userinfo")
{
}

bool QRadiusManager::open()
{
	if( isConnected() )
		close();

	m_db = QSqlDatabase::addDatabase("QMYSQL");
	m_db.setUserName( m_connInfo.userName() );
	m_db.setPassword( m_connInfo.userPass() );
	m_db.setDatabaseName( m_dataBaseName );
	m_db.setPort( m_connInfo.hostPort() );
	m_db.setHostName( m_connInfo.hostIPv4().toString() );

	return m_db.open();
}

void QRadiusManager::close()
{
	m_db.close();
}

bool QRadiusManager::updateRemoteData(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::PPPSecret )
	{
		QString sql = QString("INSERT INTO %1 (%2) VALUES(%3)")
				.arg(m_usersTableName)
				.arg("username")
				.arg(static_cast<const ROSPPPSecret &>(rosData).userName());
		return QSqlQuery(sql, m_db).exec(sql);
	}
	return true;
}


bool QRadiusManager::requestAll(DataTypeID dataTypeID)
{
	if( isConnected() && (dataTypeID == DataTypeID::PPPSecret) )
	{
		QString sqlString = QString("SELECT * FROM %1").arg(m_usersTableName);
		QSqlQuery sqlQuery(sqlString, m_db);

		while( sqlQuery.next() )
		{
			sqlQuery.value(0);
			QString country = sqlQuery.value(0).toString();
		}
	}
	return true;
}
#endif
