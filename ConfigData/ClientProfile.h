#ifndef CLIENTPROFILE_H
#define CLIENTPROFILE_H

#include <QStringList>

#include "Utils/QIniFile.h"

struct ClientProfileData
{
private:
	QString m_name;
	QString m_group;
	bool m_disabled;	// Si este perfil es para usuarios dados de baja.
	bool m_internal;	// Si este perfil es interno y no ha de usarse.
	bool m_default;		// Si este perfil es el perfil por defecto.

public:
	const QString &profileName() const				{ return m_name;		}
	void setProfileName(const QString &profileName)	{ m_name = profileName;	}

	const QString &groupName() const			{ return m_group;	}
	void setGroupName(const QString &group)	{ m_group = group;	}

	bool isInternalProfile() const		{ return m_internal;}
	void setInternalProfile(bool i)		{ m_internal = i;	}

	bool isDisabledProfile() const		{ return m_disabled;}
	void setDisabledProfile(bool d)		{ m_disabled = d;	}

	bool isDefaultProfile() const		{ return m_default;	}
	void setDefaultProfile(bool d)		{ m_default = d;	}

	explicit ClientProfileData(const QString &saveString) :
		m_disabled(false),
		m_internal(false),
		m_default(false)
	{
		fromSaveString(saveString);
	}
	ClientProfileData() :
		m_disabled(false),
		m_internal(false),
		m_default(false)
	{	}

	bool operator==(const QString &profileName) const
	{
		return m_name == profileName;
	}
	bool operator==(const ClientProfileData &clientProfileData) const
	{
		return m_name == clientProfileData.profileName();
	}

	QString saveString()const;
	void fromSaveString(const QString &saveString);
};

// TODO: Doesn't this fits better in a map?
class QClientProfileList : public QList<ClientProfileData>
{
	// TODO: caching current default and disabled profiles to improve lookup speed.
public:
	void append(const ClientProfileData &saveString);

	bool contains(const QString &profileName) const;

	void save(QIniData &cnfgData) const;
	void load(const QIniData &cnfgData);

	int indexOfDisabledProfile()const;
	ClientProfileData disabledProfile()const;
	bool isDisabledProfile(const QString &profileName)const;

	int indexOfDefaultProfile()const;
	ClientProfileData defaultProfile()const;
	bool isDefaultProfile(const QString &profileName)const;

	int isInternalProfile(const QString &profileName)const;

	void setDisabledProfile(int index);
	void setDefaultProfile(int index);
	void setProfileGroupName(int index, const QString &name);

	QStringList profileNames()const;
	// Return all profile names excluding disabled and internals.
	QStringList regularProfileNames()const;
};

#endif // CLIENTPROFILE_H
