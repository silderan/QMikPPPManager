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

public:
	ROSDataManagerBase(const QString &path) : m_path(path)
	{
		Q_ASSERT( path.count() > 2 );
		Q_ASSERT( path[0] == '/' );
		Q_ASSERT( path.endsWith('/') );
	}
	virtual ~ROSDataManagerBase()
	{	}

	const QString &routerName() const				{ return m_routerName;		}
	void setRouterName(const QString &routerName)	{ m_routerName = routerName;}

	const QString &path() const			{ return m_path;		}

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
	}
	virtual ROSDataBase *onROSModReply(const ROS::QSentence &sentence) = 0;

	virtual QString getallCommand()		{ return QString("%1getall").arg(m_path);	}
	virtual QString listenCommand()		{ return QString("%1listen").arg(m_path);	}

	virtual QString setCommand()		{ return QString("%1set").arg(m_path);		}
	virtual QString addCommand()		{ return QString("%1add").arg(m_path);		}
	virtual QString removeCommand()		{ return QString("%1remove").arg(m_path);	}

	virtual QStringList getallQueries()	{ return QStringList() << "#|";	}
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

		T *t = new T(m_routerName);
		t->fromSentence(m_routerName, sentence);
		m_idDataMapP.insert( sentence.getID(), t );
		return t;
	}
};
#endif // ROSDATAMANAGERBASE_H

