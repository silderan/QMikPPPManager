#ifndef QTREEWIDGETBASE_H
#define QTREEWIDGETBASE_H

#include <QTableWidget>

#include "../ROSDataBasics.h"

/**
 * @brief The QTableWidgetBase class TreeWidget class with comon features for ROS data control.
 */

class QTableWidgetBase : public QTableWidget
{
	Q_OBJECT

	int m_routerIDColumn;

public:
	explicit QTableWidgetBase(QWidget *parent = Q_NULLPTR);
	~QTableWidgetBase();

	int rowOf(int colKey, const QString &cellText);
	int rowOf(const QString &routerName, const QString &dataID);
	void setCellText(int row, int col, const QString &text, Qt::ItemFlags itemFlags = Qt::NoItemFlags);
	QString cellText(int row, int col, const QString &defaultValue = QString())const;
	int cellInt(int row, int col, int defaultValue = -1)const;

	void addCellRoutersID(int row, int col, const QString &routerName, const QString &dataID);
	void delCellRoutersID(int row, const QString &routerName);

	const QRouterIDMap &routerIDMap(int row) const;
	inline QString dataID(int row, const QString &routerName) const	{ return routerIDMap(row).value(routerName);	}
	inline QList<QString> routerNames(int row) const	{ return routerIDMap(row).keys();		}
	inline int routersCount(int row) const	{ return routerIDMap(row).count();	}

	inline void setRouterIDColumn(int col)	{ m_routerIDColumn = col;	}

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
	// Internally called when new data arrived and row cells mut be updated.
	// It's not necessary to override this one because this will call setupRow rowOf virtual funcions.
	virtual void onRemoteDataModified(const ROSDataBase &rosData);
	// Intercally called when data from ROS informs of data deletion.
	// It's not necessary to override. It will loolup row and perform the router-id pair lookup, update data and row deletion if necessary.
	virtual void onRemoteDataDeleted(const ROSDataBase &rosData);
	// Internally called when rosData must been requested.
	// Base function does nothing because the only known data are router-id and there are many of them.
	// So, derived classes must override this funcion and fillup all data.
	// pointer must be globally allocated and will be deleted later by the caller.
	virtual ROSDataBase *getRosData(int row) = 0;

public slots:
	// Must be called at ROS reply.
	// Peeps rosData to see if it's a modification or deletion and calls onRemoteDataModified or onRemoteDataDeleted acordingly.
	void onRemoteDataReceived(const ROSDataBase &rosData);

	void removeData(int row);
	inline void removeCurrentData()		{ removeData(currentRow());	}

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);
};

#endif // QTREEWIDGETBASE_H
