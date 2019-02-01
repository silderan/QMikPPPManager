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
	return QString("%1,%2,%3").
			arg("2",	// Version
				m_name,
				m_group );
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
			if( data.count() >= 3 )
			{
				m_name		= data[1];
				m_group		= data[2];
				if( data.count() == 6 )
				{
					if( data[3] == "internalProfile" )
						m_group.clear();
					if( data[4] == "disabledUser" )
						m_group = serviceCanceledGroupName();
				}
			}
			break;
		default:
			break;
		}
	}
}

void QClientProfileMap::save(QIniData &cnfgData) const
{
	QMapIterator<QString, ClientProfileData> it(*this);
	int i = 0;
	while( it.hasNext() )
	{
		it.next();
		i++;
		cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)] = it.value().saveString();
	}
}

void QClientProfileMap::load(const QIniData &cnfgData)
{
	QString saveString;
	for( int i = 1; !(saveString = cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)]).isEmpty(); ++i )
	{
		ClientProfileData cl(saveString);
		insert( cl );
	}
}

void QClientProfileMap::insert(const ClientProfileData &clientProfileData)
{
	QMap::insert(clientProfileData.pppProfileName(), clientProfileData);
}


ClientProfileData QClientProfileMap::serviceCanceledProfile() const
{
	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		if( it.value().isServiceCanceledProfile() )
			return it.value();
	}
	return ClientProfileData("");
}

QString QClientProfileMap::groupName(const QString &clientProfileName) const
{
	foreach( const ClientProfileData &clientProfileData, *this )
	{
		if( clientProfileData.pppProfileName() == clientProfileName )
			return clientProfileData.groupName();
	}
	return QString();
}

QStringList QClientProfileMap::profileNames() const
{
	QStringList rtn;

	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		rtn.append(it.value().pppProfileName());
	}

	return rtn;
}

QStringList QClientProfileMap::groupNames() const
{
	QStringList rtn;

	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		if( !rtn.contains(it.value().groupName()) )
			rtn.append(it.value().groupName());
	}
	return rtn;
}

bool QClientProfileMap::containsProfileName(const QString &profileName)
{
	return QMap::contains(profileName);
}

bool QClientProfileMap::containsGroupName(const QString &groupName)
{
	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		if( it.value().groupName() == groupName )
			return true;
	}
	return false;
}

QStringList QClientProfileMap::regularProfileNames() const
{
	QStringList rtn;

	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		if( !it.value().isServiceCanceledProfile() )
			rtn.append(it.value().pppProfileName());
	}
	return rtn;
}
