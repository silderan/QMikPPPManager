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

#include <QObject>

#include "ClientProfile.h"

#define KEY_CLIENT_PROFILE_DATA				("client-profile-data")
#define KEY_CLIENT_PROFILE_DATA_LIST(_i)	(QString("client-profile-data-list-%1").arg(_i))

QString ClientProfileData::serviceCanceledGroupName()
{
	return QObject::tr("[servicio cancelado]");
}

QString ClientProfileData::saveString() const
{
	return QString("%1,%2,%3")
			.arg("2",	// Version
				mName,
				mGroup);
}

void ClientProfileData::fromSaveString(const QString &saveString)
{
	QStringList data = saveString.split(',');
	if( data.count() > 1 )
	{
		switch( data[0].toUInt() )
		{
		case 1:
		case 2:
		case 3:
			if( data.count() >= 3 )
			{
				mName		= data[1];
				mGroup		= data[2];
			}
			break;
		default:
			break;
		}
	}
}

void QClientProfileMap::save(QIniData &cnfgData) const
{
	int i = 0;
	for( const ClientProfileData &data : *this )
	{
		i++;
		cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)] = data.saveString();
	}
}

void QClientProfileMap::load(const QIniData &cnfgData)
{
	QString saveString;
	for( int i = 1; !(saveString = cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)]).isEmpty(); ++i )
		insert( ClientProfileData(saveString) );
}

void QClientProfileMap::insert(const ClientProfileData &clientProfileData)
{
	QMap::insert(clientProfileData.pppProfileName(), clientProfileData);
}


ClientProfileData QClientProfileMap::serviceCanceledProfile() const
{
	for( const ClientProfileData &data : *this )
	{
		if( data.isServiceCanceledProfile() )
			return data;
	}
	return ClientProfileData("");
}

ClientProfileData QClientProfileMap::clientProfile( const QString &profileName ) const
{
	return operator[](profileName);
}

QStringList QClientProfileMap::profileNames() const
{
	return keys();
}

QStringList QClientProfileMap::groupNames() const
{
	QStringList rtn;

	for( const ClientProfileData &data : *this )
		if( !rtn.contains(data.groupName()) )
			rtn.append( data.groupName() );

	return rtn;
}

bool QClientProfileMap::containsProfileName(const QString &profileName)
{
	return QMap::contains(profileName);
}

bool QClientProfileMap::containsGroupName(const QString &groupName)
{
	for( const ClientProfileData &data : *this )
		if( data.groupName() == groupName )
			return true;
	return false;
}

QStringList QClientProfileMap::regularProfileNames() const
{
	QStringList rtn;

	for( const ClientProfileData &data : *this )
	{
		if( !data.isServiceCanceledProfile() )
			rtn.append( data.pppProfileName() );
	}
	return rtn;
}
