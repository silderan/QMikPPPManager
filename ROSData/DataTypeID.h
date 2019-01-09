#ifndef DATATYPEID_H
#define DATATYPEID_H

/*
 * This enumerates all types of data requested from ROS (and future other sources)
 * Any new Data manager must have his own type here.
 * And all derived classes from DataBase must set this type in constructor.
 */
typedef enum
{
	APIUser,
	APIUsersGroup,
	PPPProfile,
	Interface,
	BridgePorts,
	IPAddress,
	IPPool,
	TotalIDs
}DataTypeID;


#endif // DATATYPEID_H
