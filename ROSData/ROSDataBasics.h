#ifndef QROSDATABASICS_H
#define QROSDATABASICS_H

#include <QString>

#include <QMap>
#include <QMapIterator>

#include "ROSAPI/Comm.h"

class ROSDataBase
{
	QString m_routerName;
	QString m_dataID;
	bool m_delete;

public:
	ROSDataBase(const QString &routerName, const QString &dataID = QString()) :
		m_routerName(routerName),
		m_dataID(dataID),
		m_delete(false)
	{	}
	virtual ~ROSDataBase()
	{	}


	inline const QString &dataID()	const		{ return m_dataID;	}
	inline void setDataID(const QString &id)	{ m_dataID = id;	}

	inline const QString &routerName() const				{ return m_routerName;		}
	inline void setRouterName(const QString &routerName)	{ m_routerName = routerName;}

	inline bool deleting()const					{ return m_delete;	}
	inline void setDeleting(bool d)				{ m_delete = d;		}

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
