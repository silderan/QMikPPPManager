/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#include "QROSDataTableWidget.h"

#include <QTreeWidgetItem>

#include "QRoutersLineEdit.h"

QROSDataTableWidget::QROSDataTableWidget(QWidget *papi) : QTableWidget(papi),
	m_routerIDColumn(-1), m_routerColumn(-1)
{
	connect( this, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChanged(int,int)) );
}

QROSDataTableWidget::~QROSDataTableWidget()
{

}

int QROSDataTableWidget::rowOf(const QString &routerName, const QString &rosObjectID)
{
	Q_ASSERT( !routerName.isEmpty() );

	// It's not an error because could be some lookup events before the table data has been populated.
	if( (m_routerIDColumn == -1) && (m_routerColumn == -1) )
	{
		qWarning("Cannot lookup row by router or router/rosObjectID if nor routerColumn neither routerIDColumn are not defined yet");
		return -1;
	}

	if( (m_routerIDColumn != -1) || (m_routerColumn != -1) )
	{
		for( int row = 0; row < rowCount(); ++row )
		{
			if( cellWidget(row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn) )
			{
				QRoutersLineEdit* routerLineEdit = static_cast<QRoutersLineEdit*>(cellWidget(row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn));
				Q_ASSERT( routerLineEdit );
				if( !rosObjectID.isEmpty() )
				{
					if( routerLineEdit->rosObjectID(routerName) == rosObjectID )
						return row;
				}
				else
				{
					if( !routerLineEdit->rosObjectID(routerName).isEmpty() )
						return row;
				}
			}
		}
	}

	return -1;
}

int QROSDataTableWidget::rowOf(int colKey, const QString &cellText)
{
	Q_ASSERT( (colKey >= 0) && (colKey < columnCount()) );
	Q_ASSERT( !cellText.isEmpty() );

	for( int row = 0; row < rowCount(); ++row )
		if( item(row, colKey)->text() == cellText )
			return row;

	return -1;
}

void QROSDataTableWidget::setCellText(int row, int col, const QString &text, Qt::ItemFlags itemFlags)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( !item(row, col) )
		setItem(row, col, new QTableWidgetItem() );

	item(row, col)->setText(text);
	item(row, col)->setFlags(itemFlags | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

QString QROSDataTableWidget::cellText(int row, int col, const QString &defaultValue) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

int QROSDataTableWidget::cellInt(int row, int col, int defaultValue) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );

	if( item(row, col) != Q_NULLPTR )
		return item(row, col)->text().toInt();
	qWarning("Ningun item en la fila %d, columna %d", row, col);
	return defaultValue;
}

void QROSDataTableWidget::addCellRoutersID(int row, int col, const QString &routerName, const QString &rosObjectID)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (col >= 0) && (col < columnCount()) );
	Q_ASSERT( (m_routerIDColumn == -1) || (m_routerIDColumn == col) );

	if( cellWidget(row, col) == Q_NULLPTR )
	{
		setCellWidget( row, col, new QRoutersLineEdit() );
		m_routerIDColumn = col; // This is used later to increase the deletion speed.
	}
	static_cast<QRoutersLineEdit*>(cellWidget(row, col))->addRouterID(routerName, rosObjectID);
}

void QROSDataTableWidget::delCellRoutersID(int row, const QString &routerName)
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (m_routerIDColumn >= 0) && (m_routerIDColumn < columnCount()) );
	Q_ASSERT( cellWidget(row, m_routerIDColumn) != Q_NULLPTR );
	Q_ASSERT( static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn)) != Q_NULLPTR );

	static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn))->delRouter(routerName);
}

const QRouterIDMap &QROSDataTableWidget::routerIDMap(int row) const
{
	Q_ASSERT( (row >= -1) && (row < rowCount()) );
	Q_ASSERT( (m_routerIDColumn >= 0) && (m_routerIDColumn < columnCount()) );
	Q_ASSERT( cellWidget(row, m_routerIDColumn) != Q_NULLPTR );
	Q_ASSERT( static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn)) != Q_NULLPTR );

	return static_cast<QRoutersLineEdit*>(cellWidget(row, m_routerIDColumn))->routerIDMap();
}

void QROSDataTableWidget::setFancyItemDelegateForColumn(int column, QFancyItemDelegate *delegate)
{
	QTableWidget::setItemDelegateForColumn( column, delegate );
	delegate->setAllowChangeCallback( [this] (const QModelIndex &index,const QString &newValue) {
			return allowModelIndexDataChange(index, newValue);
		} );
}

int QROSDataTableWidget::rowOf(const ROSDataBase &rosData)
{
	return rowOf(rosData.routerName(), rosData.rosObjectID());
}

bool QROSDataTableWidget::allowModelIndexDataChange(const QModelIndex &index, const QString &newData)
{
	ROSDataBase *rosData = getRosData(index.row());
	updateROSData(rosData, index.row(), index.column(), newData);
	emit dataModified( *rosData, routerIDMap(index.row()) );
	delete rosData;
	return false;
}

void QROSDataTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	if( (m_routerIDColumn != -1) || (m_routerColumn != -1) )
		addCellRoutersID( row, (m_routerIDColumn != -1) ? m_routerIDColumn : m_routerColumn, rosData.routerName(), rosData.rosObjectID() );
}

void QROSDataTableWidget::addNewRow(const ROSDataBase &rosData)
{
	Q_ASSERT( rosData.routerName().isEmpty() );
	Q_ASSERT( rosData.rosObjectID().isEmpty() );

	blockSignals(true);

	int row = rowCount();
	insertRow( row );
	setupRow( row, rosData );

	blockSignals(false);
}

void QROSDataTableWidget::onROSModReply(const ROSDataBase &rosData)
{
	Q_ASSERT( !rosData.routerName().isEmpty() );
	Q_ASSERT( !rosData.rosObjectID().isEmpty() );

	blockSignals(true);
	int row = rowOf( rosData );

	if( (row >= rowCount()) || (row < 0) )
		insertRow( row = rowCount() );
	setupRow( row, rosData );

	blockSignals(false);
}

void QROSDataTableWidget::onROSDelReply(const QString &routerName, const QString &rosObjectID)
{
	// It's not an error because could be some lookup events before the table data has been populated.
	if( (m_routerIDColumn == -1) && (m_routerColumn == -1) )
	{
		qWarning("Cannot lookup row by router or router/rosObjectID if nor routerColumn neither routerIDColumn are not defined yet");
		return;
	}

	blockSignals(true);
	int row;
	while( (row = rowOf(routerName, rosObjectID)) != -1 )
	{
		delCellRoutersID(row, routerName);
		if( routersCount(row) == 0 )
			removeRow(row);
	}
	blockSignals(false);
}

void QROSDataTableWidget::removeData(int row)
{
	if( (row != -1) )
	{
		ROSDataBase *rosData = getRosData(row);
		rosData->setDeleting(true);
		emit dataModified( *rosData, routerIDMap(row) );
		delete rosData;
	}
}

void QROSDataTableWidget::onCellChanged(int row, int col)
{
	Q_UNUSED(col);
	ROSDataBase *rosData = getRosData(row);
	emit dataModified( *rosData, routerIDMap(row) );
	delete rosData;
}
