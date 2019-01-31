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
	void setupRow(int row, const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	int rowOf(const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	ROSDataBase *getRosData(int row) Q_DECL_OVERRIDE;

	void updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue) Q_DECL_OVERRIDE;
};

#endif // QROSAPIUSERSGROUPTABLEWIDGET_H
