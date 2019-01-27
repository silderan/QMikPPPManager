#ifndef QTREEWIDGETBASE_H
#define QTREEWIDGETBASE_H

#include <QTableWidget>

#include "QComboBoxItemDelegate.h"
#include "../ROSData/ROSDataBasics.h"

/**
 * @brief The QTableWidgetBase class TreeWidget class with comon features for ROS data control.
 */

class QROSDataTableWidget : public QTableWidget
{
	Q_OBJECT

	int m_routerIDColumn;
	int m_routerColumn;

public:
	explicit QROSDataTableWidget(QWidget *parent = Q_NULLPTR);
	~QROSDataTableWidget();

	int rowOf(int colKey, const QString &cellText);
	int rowOf(const QString &routerName, const QString &rosObjectID);
	void setCellText(int row, int col, const QString &text, Qt::ItemFlags itemFlags = Qt::NoItemFlags);
	QString cellText(int row, int col, const QString &defaultValue = QString())const;
	int cellInt(int row, int col, int defaultValue = -1)const;

	void addCellRoutersID(int row, int col, const QString &routerName, const QString &rosObjectID);
	void delCellRoutersID(int row, const QString &routerName);

	const QRouterIDMap &routerIDMap(int row) const;
	inline QString dataID(int row, const QString &routerName) const	{ return routerIDMap(row).value(routerName);	}
	inline QList<QString> routerNames(int row) const	{ return routerIDMap(row).keys();		}
	inline int routersCount(int row) const	{ return routerIDMap(row).count();	}

	inline void setRouterIDColumn(int col)	{ m_routerIDColumn = col;	}

	void setFancyItemDelegateForColumn(int column, QFancyItemDelegate *delegate);

private slots:
	void onCellChanged(int row, int col);

protected:

	// Internally called when row data must been updated.
	// Overriders must fillup all cellText. The cellRouterID will be filled up calling base function
	virtual void setupRow(int row, const ROSDataBase &rosData);
	// Internally called when needs to lookup the row.
	// Base function performs a routerName-dataID lookup via rowOf(const QString &routerName, const QString &dataID)
	// Overriders must to lookup based on their specific
	virtual int rowOf(const ROSDataBase &rosData);
	// Internally called when rosData is needed because of table row modification or deletion.
	// Base function does nothing because the only known data are router-id and there are many of them.
	// So, derived classes must override this funcion and fillup all data.
	// Pointer must be globally allocated and will be deleted later by the caller.
	virtual ROSDataBase *getRosData(int row) = 0;
	// Internally called one column has been changed but before it's actually changed in table.
	// Base function does nothing because the only known data are router-id.
	// So, derived classes must override this funcion and update data of the rosData member up to changedColumn.
	virtual void updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue);
	// Called by delegates before data changes.
	// Base funcion returns false and sends data to ROS. With this, data shown in table remains untouched and just will be
	// updated when it comes from ROS. Un case of ROS error, as local data remained unchanged, is consistent with remote one.
	// This function calls getROSData(int row, int changedColumn, const QString &newValue);
	// Overriders shouldn't change this behaviour.
	virtual bool allowModelIndexDataChange( const QModelIndex &index, const QString &newData );

public:
	void addNewRow(const ROSDataBase &rosData);
	// Must be called when new data arrived and row cells mut be updated.
	// It's not necessary to override this one because this will call setupRow rowOf virtual funcions.
	virtual void onROSModReply(const ROSDataBase &rosData);
	// Must be called when data from ROS informs of data deletion.
	// It's not necessary to override. It will loolup row and perform the router-id pair lookup, update data and row deletion if necessary.
	// On single router discconnection must be called also once without rosObjectID and this will remove all router's data.
	virtual void onROSDelReply(const QString &routerName, const QString &rosObjectID);
	virtual void onROSDone(const QString &/*routerName*/)
	{	}

public slots:
	void removeData(int row);
	inline void removeCurrentData()		{ removeData(currentRow());	}

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);
};

#endif // QTREEWIDGETBASE_H
