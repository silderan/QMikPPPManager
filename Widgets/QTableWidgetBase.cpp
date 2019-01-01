#include "QTableWidgetBase.h"

#include <QTreeWidgetItem>

#include "QRoutersLineEdit.h"

QTableWidgetBase::QTableWidgetBase(QWidget *parent) : QTableWidget(parent)
{

}

QTableWidgetBase::~QTableWidgetBase()
{

}

int QTableWidgetBase::rowOf(const QString &text, int colKey)
{
	for( int row = 0; row < rowCount(); ++row )
		if( item(row, colKey)->text() == text )
			return row;

	return -1;
}

void QTableWidgetBase::setCellText(int row, int col, const QString &text)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	if( !item(row, col) )
		setItem(row, col, new QTableWidgetItem(text) );
	else
		item(row, col)->setText(text);
}

QString QTableWidgetBase::cellText(int row, int col, const QString &defaultValue) const
{
	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

int QTableWidgetBase::cellInt(int row, int col, int defaultValue) const
{
	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text().toInt();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

void QTableWidgetBase::addCellRoutersID(int row, int col, const QString &routerName, const QString &dataID)
{
	if( cellWidget(row, col) == Q_NULLPTR )
		setCellWidget( row, col, new QRoutersLineEdit() );
	static_cast<QRoutersLineEdit*>(cellWidget(row, col))->addRouterID(routerName, dataID);
}

void QTableWidgetBase::delCellRoutersID(int row, int col, const QString &routerName)
{
	static_cast<QRoutersLineEdit*>(cellWidget(row, col))->delRouter(routerName);
}

const QRouterIDMap &QTableWidgetBase::routerIDMap(int row, int col) const
{
	Q_ASSERT( cellWidget(row, col) != Q_NULLPTR );
	Q_ASSERT( static_cast<QRoutersLineEdit*>(cellWidget(row, col)) != Q_NULLPTR );

	return static_cast<QRoutersLineEdit*>(cellWidget(row, col))->routerIDMap();
}
