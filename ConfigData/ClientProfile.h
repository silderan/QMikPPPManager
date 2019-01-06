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
	inline const QString &profileName() const				{ return m_name;		}
	inline void setProfileName(const QString &profileName)	{ m_name = profileName;	}

	inline const QString &groupName() const			{ return m_group;	}
	inline void setGroupName(const QString &group)	{ m_group = group;	}

	inline bool isInternalProfile() const		{ return m_internal;}
	inline void setInternalProfile(bool i)		{ m_internal = i;	}

	inline bool isDisabledProfile() const		{ return m_disabled;}
	inline void setDisabledProfile(bool d)		{ m_disabled = d;	}

	inline bool isDefaultProfile() const		{ return m_default;	}
	inline void setDefaultProfile(bool d)		{ m_default = d;	}

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

	inline bool operator==(const QString &profileName) const
	{
		return m_name == profileName;
	}
	inline bool operator==(const ClientProfileData &clientProfileData) const
	{
		return m_name == clientProfileData.profileName();
	}

	QString saveString()const;
	void fromSaveString(const QString &saveString);
};

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
