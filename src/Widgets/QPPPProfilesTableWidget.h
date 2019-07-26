#ifndef QPPPPROFILESTABLEWIDGET_H
#define QPPPPROFILESTABLEWIDGET_H

#include "QROSDataTableWidget.h"

class QPPPProfilesTableWidget : public QROSDataTableWidget
{
	Q_OBJECT

	enum Columns
	{
		ProfileName,
		RateLimit,
		LocalAddress,
		RemoteAddress,
		Bridge,
		Routers,
		TotalColumns
	};

public:
	explicit QPPPProfilesTableWidget(QWidget *papi = Q_NULLPTR);
	~QPPPProfilesTableWidget();

	// QTableWidgetBase interface

protected:
	virtual void setupRow(int row, const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	virtual int rowOf(const ROSDataBase &rosData) Q_DECL_OVERRIDE;
	virtual ROSDataBase *getRosData(int row) Q_DECL_OVERRIDE;
	virtual void updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue) Q_DECL_OVERRIDE;
};

#endif // QPPPPROFILESTABLEWIDGET_H
