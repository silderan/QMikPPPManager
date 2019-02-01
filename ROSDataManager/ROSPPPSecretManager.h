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

#ifndef ROSPPPSECRETMANAGER_H
#define ROSPPPSECRETMANAGER_H

#include "ROSDataManagerBase.h"
#include "../ROSData/ROSSecret.h"

class ROSPPPSecretManager : public ROSDataManager<ROSPPPSecret>
{
public:
	ROSPPPSecretManager(const QString &path) : ROSDataManager(path)
	{	}

	virtual void logAdding(const ROSDataBase &newROSData) override;
	virtual void logDeleting(const ROSDataBase &oldROSData) override;
	virtual void logChange(const ROSDataBase &oldROSData, const ROSDataBase &newROSData) override;
};

#endif // ROSPPPSECRETMANAGER_H
