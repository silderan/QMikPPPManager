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

#ifndef CLIENTPROFILE_H
#define CLIENTPROFILE_H

#include <QStringList>

#include "Utils/QIniFile.h"

struct ClientProfileData
{
private:
	QString mName;
	QString mGroup;

public:
	explicit ClientProfileData(const QString &saveString = QString())
	{
		fromSaveString(saveString);
	}

	const QString &pppProfileName() const				{ return mName;		}
	void setProfileName(const QString &profileName)		{ mName = profileName;	}

	const QString &groupName() const			{ return mGroup;	}
	void setGroupName(const QString &group)		{ mGroup = group;	}

	static QString serviceCanceledGroupName();

	bool isServiceCanceledProfile() const	{ return mGroup == serviceCanceledGroupName();	}
	void setServiceCanceledProfile()		{ mGroup = serviceCanceledGroupName();	}

	bool isValid() const				{ return !mName.isEmpty() && !mGroup.isEmpty();	}

	bool operator==(const QString &profileName) const
	{
		return mName == profileName;
	}
	bool operator==(const ClientProfileData &clientProfileData) const
	{
		return mName == clientProfileData.pppProfileName();
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

	ClientProfileData clientProfile(const QString &profileName) const;
	QString groupName(const QString &clientProfileName) const	{ return clientProfile(clientProfileName).groupName();	}

	QStringList profileNames() const;
	QStringList groupNames() const;

	bool containsProfileName(const QString &profileName);
	bool containsGroupName(const QString &groupName);

	// Return all profile names excluding canceled.
	QStringList regularProfileNames()const;
};

#endif // CLIENTPROFILE_H
