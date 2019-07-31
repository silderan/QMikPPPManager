#ifndef SCHEDULERDATA_H
#define SCHEDULERDATA_H

#include "../Utils/QIniFile.h"

namespace ServiceScheduler {

enum ServiceAction
{
	NoChange,
	Activate,
	Cancel
};

class Data
{
	quint16 mYear;
	quint16 mMonth;
	QString mProfileName;
	ServiceAction mServiceAction;

public:
	Data()
		: mYear(1900), mMonth(0)
		, mProfileName("")
		, mServiceAction(ServiceAction::NoChange)
	{	}
	Data(quint16 year, quint16 month, ServiceAction serviceAction = ServiceAction::NoChange)
		: mYear(year), mMonth(month)
		, mProfileName("")
		, mServiceAction(serviceAction)
	{	}
	Data(quint16 year, quint16 month, const QString &profileName, ServiceAction serviceAction = ServiceAction::NoChange)
		: mYear(year), mMonth(month)
		, mProfileName(profileName)
		, mServiceAction(serviceAction)
	{	}
	Data(const QString &saveString)
		: Data()
	{
		fromSaveString(saveString);
	}
	QString toSaveString() const;
	void fromSaveString(const QString &saveString);
	QString serviceActionName() const;
	QString monthName() const;
	bool isYearValid() const
	{
		return (mYear >= 1900);
	}
	bool isMonthValid() const;
	static const QStringList &months();
	static quint16 monthNumber(const QString &monthName);
	quint16 monthNumber()	{ return mMonth;	}

	void setYear(quint16 y)	{ mYear = y;	}
	void setMonth(const QString &m)	{ mMonth = monthNumber(m);	}

	quint16 year() const	{ return mYear;		}
	quint16 month() const	{ return mMonth;	}

	const QString &profileName() const		{ return mProfileName;	}
	void setProfileName(const QString &p)	{ mProfileName = p;	}

	static const QStringList &serviceActionNames();
	ServiceAction serviceAction() const		{ return mServiceAction;	}
	void setServiceAction(ServiceAction s)	{ mServiceAction = s;		}
	void setServiceAction(const QString &s);
};

class DataList : public QList<Data>
{
public:
	void append(const Data &newData)
	{
		for( int i = 0; i < count(); ++i )
		{
			if( (at(i).year() == newData.year()) && (at(i).month() == newData.month()) )
			{
				replace(i, newData);
				return;
			}
			if( (at(i).year() > newData.year()) || ((at(i).year() == newData.year()) && (at(i).month() > newData.month())) )
			{
				insert(i, newData);
				return;
			}
		}
		QList::append(newData);
	}
};

class SchedulerMap
{
	const static DataList dummyData;
	QMap<QString, DataList > mData;
	QString saveFName() const;

public:
	void load();
	void save();
	QStringList userNames()	const	{ return mData.keys();	}
	const QMap<QString, DataList > &mapData() const	{ return mData;	}
	const DataList &dataList(const QString &userName) { return mData.contains(userName) ? mData[userName] : dummyData;	}
	void setDataList(const QString &userName, const DataList &dataList) { mData[userName] = dataList; }
};

}	// End namespace ServiceScheduler

extern ServiceScheduler::SchedulerMap gSchedulerData;

#endif // SCHEDULERDATA_H
