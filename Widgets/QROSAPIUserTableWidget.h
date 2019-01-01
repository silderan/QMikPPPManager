#ifndef QROSAPIUSERTABLEWIDGET_H
#define QROSAPIUSERTABLEWIDGET_H

#include <QStringList>
#include <QTableWidgetItem>

#include "QTableWidgetBase.h"
#include "../ROSAPIUser.h"

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
	~QROSAPIUserTableWidget();

	int rowByName(const QString &groupName)const;
	int addUser(const ROSAPIUser &userData);
	void removeUser(const ROSAPIUser &userData);

	inline QString userName(int row) const				{ return cellText(row, UserName);	}
	inline QString userGroup(int row) const				{ return cellText(row, GroupName);	}
	inline ROSAPIUser::Level userLevel(int row) const	{ return ROSAPIUser::level(cellText(row, UserLevel));	}

private slots:
	void onCellChanged(int row, int col);

signals:
	void userModified(const ROSAPIUser &rosAPIUser, const QRouterIDMap &routerIDMap);
};

#endif // QROSAPIUSERTABLEWIDGET_H
