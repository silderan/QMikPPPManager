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
	QMap::insert(clientProfileData.profileName(), clientProfileData);
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

QStringList QClientProfileMap::profileNames() const
{
	QStringList rtn;

	QMapIterator<QString, ClientProfileData> it(*this);

	while( it.hasNext() )
	{
		it.next();
		rtn.append(it.value().profileName());
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
			rtn.append(it.value().profileName());
	}
	return rtn;
}
