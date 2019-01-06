#ifndef QPPPPROFILESTABLEWIDGET_H
#define QPPPPROFILESTABLEWIDGET_H

#include "QTableWidgetBase.h"

class QPPPProfilesTableWidget : public QTableWidgetBase
{
	Q_OBJECT

	enum Columns
	{
		ProfileNameColumn,
		RateLimitColumn,
		LocalAddressColumn,
		RemoteAddressColumn,
		BridgeColumn,
		RoutersColumn,
		TotalColumns
	};

public:
	explicit QPPPProfilesTableWidget(QWidget *papi = Q_NULLPTR);
	~QPPPProfilesTableWidget();

	// QTableWidgetBase interface

protected:
	virtual void setupRow(int row, const ROSDataBase &rosData);
	virtual int rowOf(const ROSDataBase &rosData);
	virtual ROSDataBase *getRosData(int row);
};

#endif // QPPPPROFILESTABLEWIDGET_H
