#ifndef SCHEDULERDATA_H
#define SCHEDULERDATA_H

#include "../Utils/QIniFile.h"

#include <QDate>
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
	ServiceAction mServiceAction;
	QString mPppoeProfileName;
	QString mOltProfileName;

public:
	Data()
		: mYear(quint16(QDate::currentDate().year())), mMonth(quint16(QDate::currentDate().month()))
		, mServiceAction(ServiceAction::NoChange)
		, mPppoeProfileName("")
	{	}

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

	const QString &profileName() const		{ return mPppoeProfileName;	}
	void setProfileName(const QString &p)	{ mPppoeProfileName = p;	}

	const QString &pppoeProfileName() const		{ return mPppoeProfileName;	}
	void setPppoeProfileName(const QString &p)	{ mPppoeProfileName = p;	}

	const QString &oltProfileName() const		{ return mPppoeProfileName;	}
	void setOltProfileName(const QString &p)	{ mPppoeProfileName = p;	}

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

class SchedulerMap : public QMap<QString, DataList>
{
	const static DataList dummyData;
	QString saveFName() const;

public:
	void load();
	void save();
	QStringList userNames()	const	{ return keys();	}
	const DataList &constDataList(const QString &userName) { return contains(userName) ? dataList(userName) : dummyData;	}
	DataList &dataList(const QString &userName)	{ return operator[](userName);	}
	void setDataList(const QString &userName, const DataList &list) { dataList(userName) = list; }
};

using SchedulerMapIterator = QMapIterator<QString, DataList>;


}	// End namespace ServiceScheduler

extern ServiceScheduler::SchedulerMap gSchedulerData;

#endif // SCHEDULERDATA_H
