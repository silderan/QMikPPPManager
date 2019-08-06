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
	int mDay;		// 0 = Firsts days of the month. -1 = last days of the month.
	ServiceAction mServiceAction;
	QString mSpeedProfileName;

public:
	Data()
	    : mYear(quint16(QDate::currentDate().year())), mMonth(quint16(QDate::currentDate().month())), mDay(0)
		, mServiceAction(ServiceAction::NoChange)
		, mSpeedProfileName("")
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
	quint16 year() const	{ return mYear;		}

	quint16 month() const	{ return mMonth;	}
	void setMonth(const QString &m)	{ mMonth = monthNumber(m);	}

	int monthDay() const;
	bool isMonthDay() const;
	bool isFirstsDays() const;
	bool isLastsDays() const;
	void setDay(int d);
	void setFirstsDays();
	void setLastsDays();
	static const QStringList &dayNames();
	static int lastDaysIndex();
	static int firstDaysIndex();
	static int monthDayToArrayIndex(int d);
	static int arrayIndexToMonthDay(int d);
	int dayIndex();
	void setDay(QString name);
	QString dayName()const;

	const QString &profileName() const		{ return mSpeedProfileName;	}
	void setProfileName(const QString &p)	{ mSpeedProfileName = p;	}

	const QString &speedProfileName() const		{ return mSpeedProfileName;	}
	void setSpeedProfileName(const QString &p)	{ mSpeedProfileName = p;	}

	static const QStringList &serviceActionNames();
	ServiceAction serviceAction() const		{ return mServiceAction;	}
	void setServiceAction(ServiceAction s)	{ mServiceAction = s;		}
	void setServiceAction(const QString &s);
	bool operator!=(const Data &other) const;
	bool operator==(const Data &other) const;
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
	bool operator==(const DataList &dataList) const;
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
	bool setDataList(const QString &userName, const DataList &list);

	void changeUserName(const QString &oldUserName, const QString &newUserName);
};

using SchedulerMapIterator = QMapIterator<QString, DataList>;


}	// End namespace ServiceScheduler

extern ServiceScheduler::SchedulerMap gServiceSchedulerMap;

#endif // SCHEDULERDATA_H
