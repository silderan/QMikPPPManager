#include "ClientProfile.h"

#define KEY_CLIENT_PROFILE_DATA				("client-profile-data")
#define KEY_CLIENT_PROFILE_DATA_LIST(_i)	(QString("client-profile-data-list-%1").arg(_i))

void QClientProfileList::append(const ClientProfileData &s)
{
	int i;

	// Ensures that only one profile is for disabled users.
	if( s.isDisabled() )
	{
		i = indexOfDisabled();
		if( i != -1 )
			(*this)[i].setDisabled(false);
	}
	// Ensures that only one profile is the default one.
	if( s.isDefault() )
	{
		i = indexOfDefault();
		if( i != -1 )
			(*this)[i].setDefault(false);
	}

	i = indexOf(s);
	if( i == -1 )
		QList::append(s);
	else
		(*this)[i] = s;
}

bool QClientProfileList::contains(const QString &s) const
{
	for( int i = 0; i < count(); i++ )
		if( at(i) == s )
			return true;
	return false;
}

QString ClientProfileData::saveString() const
{
	return QString("%1,%2,%3,%4,%5,%6,%7,%8").
			arg("1",	// Version
				m_name,
				m_group,
				QString::number(m_rxKbps),
				QString::number(m_txKbps),
				m_internal ? "internalProfile" : "usable",
				m_disabled ? "disabledUser" : "regularUser",
				m_default ? "defaultProfile" : "regularProfile" );
}

void ClientProfileData::fromSaveString(const QString &saveString)
{
	QStringList data = saveString.split(',');
	if( data.count() > 1 )
	{
		switch( data[0].toUInt() )
		{
		case 1:
			if( data.count() == 7 )
			{
				m_name		= data[1];
				m_group		= data[2];
				m_rxKbps	= data[3].toUInt();
				m_txKbps	= data[4].toUInt();
				m_internal	= data[5] == "internalProfile";
				m_disabled	= data[6] == "disabledUser";
				m_disabled	= data[6] == "disabledUser";
			}
			break;
		default:
			break;
		}
	}
}

void QClientProfileList::save(QIniData &cnfgData) const
{
	for( int i = 0; i < count(); ++i )
		cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)] = at(i).saveString();
}

void QClientProfileList::load(const QIniData &cnfgData)
{
	QString saveString;
	for( int i = 0; !(saveString = cnfgData[KEY_CLIENT_PROFILE_DATA_LIST(i)]).isEmpty(); ++i )
		append(ClientProfileData(saveString));
}

int QClientProfileList::indexOfDisabled() const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).isDisabled() )
			return i;
	return -1;
}

ClientProfileData QClientProfileList::disabledProfile() const
{
	int i = indexOfDisabled();
	if( i != -1 )
		return at(i);
	return ClientProfileData();
}

bool QClientProfileList::isDisabledProfile(const QString &profileName) const
{
	return disabledProfile().name() == profileName;
}

int QClientProfileList::indexOfDefault() const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).isDefault() )
			return i;
	return -1;
}

ClientProfileData QClientProfileList::defaultProfile() const
{
	int i = indexOfDefault();
	if( i != -1 )
		return at(i);
	return ClientProfileData();
}

bool QClientProfileList::isDefaultProfile(const QString &profileName) const
{
	return defaultProfile().name() == profileName;
}

int QClientProfileList::isInternalProfile(const QString &profileName) const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).name() == profileName )
			return at(i).isInternal();
	return false;
}

void QClientProfileList::setDisabledProfile(int index)
{
	for( int i = 0; i < count(); ++i )
		(*this)[i].setDisabled(i == index);
}

void QClientProfileList::setDefaultProfile(int index)
{
	for( int i = 0; i < count(); ++i )
		(*this)[i].setDefault(i == index);
}

void QClientProfileList::setProfileGroupName(int index, const QString &name)
{
	if( index < count() )
		(*this)[index].setGroup(name);
}

QStringList QClientProfileList::profileNames() const
{
	QStringList rtn;
	for( int i = 0; i < count(); ++i )
		rtn.append( at(i).name() );

	return rtn;
}

QStringList QClientProfileList::regularProfileNames() const
{
	QStringList rtn;

	for( int i = 0; i < count(); ++i )
		if( !at(i).isDisabled() && !at(i).isInternal() )
			rtn.append( at(i).name() );

	return rtn;
}
