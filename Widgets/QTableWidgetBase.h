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

public:
	explicit QTableWidgetBase(QWidget *parent = 0);
	~QTableWidgetBase();

	int rowOf(const QString &text, int colKey = 0);
	void setCellText(int row, int col, const QString &text);
	QString cellText(int row, int col, const QString &defaultValue = QString())const;
	int cellInt(int row, int col, int defaultValue = -1)const;

	void addCellRoutersID(int row, int col, const QString &routerName, const QString &dataID);
	void delCellRoutersID(int row, int col, const QString &routerName);

	const QRouterIDMap &routerIDMap(int row, int col) const;
	inline QString dataID(int row, int col, const QString &routerName) const	{ return routerIDMap(row, col).value(routerName);	}
	inline QList<QString> routerNames(int row, int col) const			{ return routerIDMap(row, col).keys();		}
	inline int routersCount(int row, int col) const		{ return routerIDMap(row, col).count();	}
};

#endif // QTREEWIDGETBASE_H
