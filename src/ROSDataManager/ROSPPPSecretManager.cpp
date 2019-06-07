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

#include "ROSPPPSecretManager.h"

#include "Utils/QPPPLogger.h"

void ROSPPPSecretManager::logAdding(const ROSDataBase &newROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&newROSData) != Q_NULLPTR);

	logService.logAddingSecret( static_cast<const ROSPPPSecret &>(newROSData) );
}

void ROSPPPSecretManager::logDeleting(const ROSDataBase &oldROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&oldROSData) != Q_NULLPTR);

	logService.logDeletingSecret( static_cast<const ROSPPPSecret &>(oldROSData) );
}

void ROSPPPSecretManager::logChange(const ROSDataBase &oldROSData, const ROSDataBase &newROSData)
{
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&oldROSData) != Q_NULLPTR);
	Q_ASSERT( dynamic_cast<const ROSPPPSecret *>(&newROSData) != Q_NULLPTR);

	logService.logChangingSecret( static_cast<const ROSPPPSecret &>(oldROSData), static_cast<const ROSPPPSecret &>(newROSData) );
}
