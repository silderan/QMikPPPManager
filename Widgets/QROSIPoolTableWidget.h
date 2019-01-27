#ifndef QROSIPOOLTABLEWIDGET_H
#define QROSIPOOLTABLEWIDGET_H

#include <QStringList>
#include <QTableWidgetItem>

#include "QROSDataTableWidget.h"
#include "../ROSData/ROSIPPool.h"

class QROSIPoolTableWidget : public QROSDataTableWidget
{
Q_OBJECT

	enum Column
	{
		PoolName,
		FirstIP,
		LastIP,
		Router,
		TotalColumns
	};

public:
	explicit QROSIPoolTableWidget(QWidget *papi = Q_NULLPTR);

	// QTableWidgetBase interface
protected:
	int rowOf(const ROSDataBase &rosData) override;
	ROSDataBase *getRosData(int row) override;
};

#endif // QROSIPOOLTABLEWIDGET_H
