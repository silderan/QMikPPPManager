#ifndef QROSAPIUSERSGROUPTABLEWIDGET_H
#define QROSAPIUSERSGROUPTABLEWIDGET_H

#include "QTableWidgetBase.h"
#include "../ROSAPIUserGroup.h"

class QROSAPIUsersGroupTableWidget : public QTableWidgetBase
{
	Q_OBJECT

	enum Columns
	{
		GroupName,
		Policy,
		Routers,
		TotalColumns
	};

public:
	explicit QROSAPIUsersGroupTableWidget(QWidget *parent = 0);
	~QROSAPIUsersGroupTableWidget();

	int addGroup(const ROSAPIUsersGroup &groupData);

	QStringList groupNames()const;

private slots:
	void onUserLevelChanged(int index);
};

#endif // QROSAPIUSERSGROUPTABLEWIDGET_H
