#ifndef QROSAPIUSERSGROUPTABLEWIDGET_H
#define QROSAPIUSERSGROUPTABLEWIDGET_H

#include "QROSDataTableWidget.h"

class QROSAPIUsersGroupTableWidget : public QROSDataTableWidget
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
	explicit QROSAPIUsersGroupTableWidget(QWidget *parent = Q_NULLPTR);
	~QROSAPIUsersGroupTableWidget()override;

	QStringList groupNames()const;

	// QTableWidgetBase interface
protected:
	void setupRow(int row, const ROSDataBase &rosData) override;
	int rowOf(const ROSDataBase &rosData) override;
	ROSDataBase *getRosData(int row) override;
};

#endif // QROSAPIUSERSGROUPTABLEWIDGET_H
