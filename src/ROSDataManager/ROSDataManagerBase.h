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

#ifndef ROSDATAMANAGERBASE_H
#define ROSDATAMANAGERBASE_H

#include <QString>
#include <QMap>
#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>

#include "../ROSAPI/QSentences.h"
#include "../ROSData/ROSDataBasics.h"

struct ROSDataManagerBase
{
protected:
	QString m_routerName;
	QString m_path;
	QMap<QString, ROSDataBase*> m_idDataMapP;
	bool m_done;

public:
	ROSDataManagerBase(const QString &path) : m_path(path), m_done(false)
	{
		Q_ASSERT( path.count() > 2 );
		Q_ASSERT( path[0] == '/' );
		Q_ASSERT( path.endsWith('/') );
	}
	virtual ~ROSDataManagerBase()
	{
		clear();
	}
	void clear()
	{
		foreach( ROSDataBase *rdb, m_idDataMapP )
			delete rdb;
		m_idDataMapP.clear();
	}

	const QString &routerName() const				{ return m_routerName;		}
	void setRouterName(const QString &routerName)	{ m_routerName = routerName;}

	const QString &path() const			{ return m_path;		}
	bool done() const	{ return m_done;	}

	ROSDataBase *rosData(const QString &dataID) const		{ return m_idDataMapP.value(dataID, Q_NULLPTR);	}
	ROSDataBasePList rosDataList() const					{ return m_idDataMapP.values();		}
	const QMap<QString, ROSDataBase *> &rosDataMap() const	{ return m_idDataMapP;				}

	void setup(const QString &routerName)
	{
		Q_ASSERT( !(m_routerName = routerName).isEmpty() );
	}

	virtual void onROSDeadReply(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !sentence.getID().isEmpty() );
		Q_ASSERT( !sentence.attribute(".dead").isEmpty() );
		Q_ASSERT( !m_routerName.isEmpty() );

		delete m_idDataMapP.take( sentence.getID() );
//		qDebug("Deleted from map:  %s:%s", m_routerName.toLatin1().constData(), sentence.getID().toLatin1().constData() );
	}
	virtual void onROSDoneReply()		{ m_done = true;	}

	virtual ROSDataBase *onROSModReply(const ROS::QSentence &sentence) = 0;

	virtual QString getallCommand()		{ return QString("%1getall").arg(m_path);	}
	virtual QString listenCommand()		{ return QString("%1listen").arg(m_path);	}

	virtual QString setCommand()		{ return QString("%1set").arg(m_path);		}
	virtual QString addCommand()		{ return QString("%1add").arg(m_path);		}
	virtual QString removeCommand()		{ return QString("%1remove").arg(m_path);	}

	virtual QStringList getallQueries()	{ return QStringList() << "#|";	}

	virtual void logAdding(const ROSDataBase &/*newROSData*/)	{	}
	virtual void logDeleting(const ROSDataBase &/*oldROSData*/)	{	}
	virtual void logChange(const ROSDataBase &/*oldROSData*/, const ROSDataBase &/*newROSData*/)	{	}
};

template <typename T>
class ROSDataManager : public ROSDataManagerBase
{
public:
	ROSDataManager(const QString &path) : ROSDataManagerBase(path)
	{	}

	ROSDataBase *onROSModReply(const ROS::QSentence &sentence)
	{
		Q_ASSERT( !sentence.getID().isEmpty() );
		Q_ASSERT( sentence.attribute(".dead").isEmpty() );
		Q_ASSERT( !m_routerName.isEmpty() );

		T *t;
		if( (t = static_cast<T*>(m_idDataMapP.value(sentence.getID(), Q_NULLPTR))) == Q_NULLPTR )
		{
			t = new T(m_routerName);
			m_idDataMapP.insert( sentence.getID(), t );
//			qDebug( "New data for %s:%s", m_routerName.toLatin1().constData(), sentence.getID().toLatin1().constData() );
		}
//		else
//			qDebug("Recovered from map:  %s:%s", m_routerName.toLatin1().constData(), sentence.getID().toLatin1().constData() );
		t->fromSentence(m_routerName, sentence);
		return t;
	}
};
#endif // ROSDATAMANAGERBASE_H

