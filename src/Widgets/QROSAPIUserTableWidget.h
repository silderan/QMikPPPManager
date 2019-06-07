#ifndef QROSAPIUSERTABLEWIDGET_H
#define QROSAPIUSERTABLEWIDGET_H

#include <QStringList>
#include <QTableWidgetItem>

#include "QROSDataTableWidget.h"
#include "../ROSData/ROSAPIUser.h"

class QROSAPIUserTableWidget : public QROSDataTableWidget
{
	Q_OBJECT

	enum Columns
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
	virtual ROSDataBase *getRosData(int row) Q_DECL_OVERRIDE;
	virtual void setupRow(int row, const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	virtual int rowOf(const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	virtual void updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue) Q_DECL_OVERRIDE;
};

#endif // QROSAPIUSERTABLEWIDGET_H
