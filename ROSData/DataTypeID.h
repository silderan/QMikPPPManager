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
