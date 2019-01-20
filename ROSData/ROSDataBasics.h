#ifndef QROSDATABASICS_H
#define QROSDATABASICS_H

#include <QString>

#include <QMap>
#include <QMapIterator>

#include "ROSAPI/Comm.h"
#include "DataTypeID.h"

class ROSDataBase
{
	DataTypeID m_dataTypeID;
	QString m_routerName;
	QString m_rosObjectID;
	QString m_comment;
	bool m_delete;

public:
	ROSDataBase(DataTypeID dataTypeID, const QString &routerName) :
		m_dataTypeID(dataTypeID),
		m_routerName(routerName),
		m_delete(false)
	{	}
	virtual ~ROSDataBase()
	{	}

	DataTypeID dataTypeID() const	{	return m_dataTypeID;	}

	const QString &rosObjectID()	const		{ return m_rosObjectID;	}
	void setROSObjectID(const QString &id)		{ m_rosObjectID = id;	}

	const QString &routerName() const				{ return m_routerName;		}
	void setRouterName(const QString &routerName)	{ m_routerName = routerName;}

	const QString &comment() const			{ return m_comment;	}
	void setComment(const QString &c)		{ m_comment = c;	}

	bool deleting()const					{ return m_delete;	}
	void setDeleting(bool d)				{ m_delete = d;		}

	virtual void fromSentence(const QString &routerName, const ROS::QSentence &s);
	virtual ROS::QSentence &toSentence(ROS::QSentence &sentence) const;
	/**
	 * @brief hasSameData
	 * Called to determine if rosData must be send to ROS.
	 * So, derived classes MUST override and check if any of their data is not identical
	 * and return false.
	 * Also dataID() shouldn't be checked. For this reason, this function is pure virtual.
	 * @return false if any data is different.
	 */
	virtual bool hasSameData(const ROSDataBase &rosData)const = 0;
};
typedef QList<ROSDataBase*> ROSDataBasePList;

class QRouterIDMap : public QMap<QString, QString>
{

public:
	QString dataID(const QString &routerName) const	{ return value(routerName);	}
};

class QRouterIDMapIterator : public QMapIterator<QString, QString>
{

public:
	QRouterIDMapIterator(const QRouterIDMap &routerIDMap) : QMapIterator(routerIDMap)
	{	}

	QString dataID() const		{ return value();	}
	QString routerName() const	{ return key();		}
};

#endif // QROSDATABASICS_H
