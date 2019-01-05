#include "ClientProfile.h"

#define KEY_CLIENT_PROFILE_DATA				("client-profile-data")
#define KEY_CLIENT_PROFILE_DATA_LIST(_i)	(QString("client-profile-data-list-%1").arg(_i))

void QClientProfileList::append(const ClientProfileData &s)
{
	int i;

	// Ensures that only one profile is for disabled users.
	if( s.isDisabledProfile() )
	{
		i = indexOfDisabledProfile();
		if( i != -1 )
			(*this)[i].setDisabledProfile(false);
	}
	// Ensures that only one profile is the default one.
	if( s.isDefaultProfile() )
	{
		i = indexOfDefaultProfile();
		if( i != -1 )
			(*this)[i].setDefaultProfile(false);
	}

	i = indexOf(s);
	if( i == -1 )
		QList::append(s);
	else
		(*this)[i] = s;
}

bool QClientProfileList::contains(const QString &profileName) const
{
	for( int i = 0; i < count(); i++ )
		if( at(i) == profileName )
			return true;
	return false;
}

QString ClientProfileData::saveString() const
{
	return QString("%1,%2,%3,%4,%5,%6").
			arg("1",	// Version
				profileName(),
				m_group,
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
			if( data.count() == 6 )
			{
				setProfileName(data[1]);
				m_group		= data[2];
				m_internal	= data[3] == "internalProfile";
				m_disabled	= data[4] == "disabledUser";
				m_default	= data[5] == "defaultProfile";
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

int QClientProfileList::indexOfDisabledProfile() const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).isDisabledProfile() )
			return i;
	return -1;
}

ClientProfileData QClientProfileList::disabledProfile() const
{
	int i = indexOfDisabledProfile();
	if( i != -1 )
		return at(i);
	return ClientProfileData("FakeDisabledProfile");
}

bool QClientProfileList::isDisabledProfile(const QString &profileName) const
{
	return disabledProfile().profileName() == profileName;
}

int QClientProfileList::indexOfDefaultProfile() const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).isDefaultProfile() )
			return i;
	return -1;
}

ClientProfileData QClientProfileList::defaultProfile() const
{
	int i = indexOfDefaultProfile();
	if( i != -1 )
		return at(i);
	return ClientProfileData("FakeDefaultProfile");
}

bool QClientProfileList::isDefaultProfile(const QString &profileName) const
{
	return defaultProfile().profileName() == profileName;
}

int QClientProfileList::isInternalProfile(const QString &profileName) const
{
	for( int i = 0; i < count(); ++i )
		if( at(i).profileName() == profileName )
			return at(i).isInternalProfile();
	return false;
}

void QClientProfileList::setDisabledProfile(int index)
{
	for( int i = 0; i < count(); ++i )
		(*this)[i].setDisabledProfile(i == index);
}

void QClientProfileList::setDefaultProfile(int index)
{
	for( int i = 0; i < count(); ++i )
		(*this)[i].setDefaultProfile(i == index);
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
		rtn.append( at(i).profileName() );

	return rtn;
}

QStringList QClientProfileList::regularProfileNames() const
{
	QStringList rtn;

	for( int i = 0; i < count(); ++i )
		if( !at(i).isDisabledProfile() && !at(i).isInternalProfile() )
			rtn.append( at(i).profileName() );

	return rtn;
}
