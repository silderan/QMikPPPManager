#ifndef QROSAPIUSERTABLEWIDGET_H
#define QROSAPIUSERTABLEWIDGET_H

#include <QStringList>
#include <QTableWidgetItem>

#include "QTableWidgetBase.h"
#include "../ROSData/ROSAPIUser.h"

class QROSAPIUserTableWidget : public QTableWidgetBase
{
	Q_OBJECT

	enum Column
	{
		UserName,
		GroupName,
		UserLevel,
		Routers,
		TotalColumns
	};

public:
	explicit QROSAPIUserTableWidget(QWidget *papi = Q_NULLPTR);
	virtual ~QROSAPIUserTableWidget()override;

	ROSAPIUser rosAPIUser(int row);
	int rowByName(const QString &groupName)const;

	inline QString userName(int row) const				{ return cellText(row, UserName);	}
	inline QString userGroup(int row) const				{ return cellText(row, GroupName);	}
	inline ROSAPIUser::Level userLevel(int row) const	{ return ROSAPIUser::level(cellText(row, UserLevel));	}

protected:
	ROSDataBase *getRosData(int row)override;
	void setupRow(int row, const ROSDataBase &rosData)override;
	int rowOf(const ROSDataBase &rosData) override;
};


#endif // QROSAPIUSERTABLEWIDGET_H
