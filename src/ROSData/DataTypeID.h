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

#ifndef DATATYPEID_H
#define DATATYPEID_H

#include <QList>
/*
 * This enumerates all types of data requested from ROS (and future other sources)
 * Any new Data manager must have his own type here.
 * And all derived classes from DataBase must set this type in constructor.
 */
typedef enum
{
	ErrorTypeID,
	APIUser,
	APIUsersGroup,
	PPPProfile,
	Interface,
	BridgePorts,
	IPAddress,
	IPPool,
	PPPSecret,
	PPPActive,
	TotalIDs
}DataTypeID;

typedef QList<DataTypeID> DataTypeIDList;
#endif // DATATYPEID_H
