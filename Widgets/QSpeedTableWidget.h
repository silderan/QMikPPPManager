#ifndef QSPEEDTABLEWIDGET_H
#define QSPEEDTABLEWIDGET_H

#include <QTableWidget>
#include <QStyledItemDelegate>

#include "Utils/ROSRateLimit.h"

class QSpeedTableWidget : public QTableWidget
{
	Q_OBJECT

	ROSRateLimit m_ROSRateLimit;
	bool m_inverted;

	void setItemText(int row, int col, const QString &text);
	void setItemSpeed(int row, int col, const ROSSpeed &rosSpeed);
	void setItemTime(int row, int col, quint32 time);

	void updateTable();

	QString checkSpeeds( const QString &direction, ROSSpeed normal, ROSSpeed burst, ROSSpeed average, quint32 seconds )const;
	void raiseWarning(const QString &error)const;

public:
	explicit QSpeedTableWidget(QWidget *parent = Q_NULLPTR);

	void setROSRateLimit(const ROSRateLimit &rosRateLimit, bool inverted = false);
	void setROSRateLimit(const QString &rosRateLimitString, bool inverted = false);

	bool getROSRateLimit(ROSRateLimit &rosRateLimit) const;
};


class QSpeedTableWidgetItemDelegate : public QStyledItemDelegate
{
public:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // QSPEEDTABLEWIDGET_H
