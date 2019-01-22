#ifndef CLIENTPROFILE_H
#define CLIENTPROFILE_H

#include <QStringList>

#include "Utils/QIniFile.h"

struct ClientProfileData
{
private:
	QString m_name;
	QString m_group;

public:
	explicit ClientProfileData(const QString &saveString = QString())
	{
		fromSaveString(saveString);
	}

	const QString &pppProfileName() const				{ return m_name;		}
	void setProfileName(const QString &profileName)	{ m_name = profileName;	}

	const QString &groupName() const			{ return m_group;	}
	void setGroupName(const QString &group)	{ m_group = group;	}

	static QString serviceCanceledGroupName();

	bool isServiceCanceledProfile() const	{ return m_group == serviceCanceledGroupName();	}
	void setServiceCanceledProfile()		{ m_group = serviceCanceledGroupName();	}

	bool isValid() const				{ return !m_name.isEmpty() && !m_group.isEmpty();	}

	bool operator==(const QString &profileName) const
	{
		return m_name == profileName;
	}
	bool operator==(const ClientProfileData &clientProfileData) const
	{
		return m_name == clientProfileData.pppProfileName();
	}

	QString saveString()const;
	void fromSaveString(const QString &saveString);
};

class QClientProfileMap : public QMap<QString, ClientProfileData>
{
public:
	void save(QIniData &cnfgData) const;
	void load(const QIniData &cnfgData);

	void insert(const ClientProfileData &clientProfileData);
	ClientProfileData serviceCanceledProfile() const;

	QString groupName(const QString &clientProfileName)const;
	QStringList profileNames() const;
	QStringList groupNames() const;

	bool containsProfileName(const QString &profileName);
	bool containsGroupName(const QString &groupName);

	// Return all profile names excluding canceled.
	QStringList regularProfileNames()const;
};

#endif // CLIENTPROFILE_H
