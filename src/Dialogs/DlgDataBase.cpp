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

#include "DlgDataBase.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTableWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QAbstractButton>

QDialogBase::QDialogBase(QWidget *papi) : QDialog(papi)
{
}

void QDialogBase::raiseWarning(const QString &info, const QString &field) const
{
	if( field.isEmpty() )
		QMessageBox::warning( const_cast<QDialogBase*>(this), windowTitle(), info );
	else
		QMessageBox::warning( const_cast<QDialogBase*>(this), windowTitle(), tr("El campo '%1' %2").arg(field, info) );
}

QObjectList QDialogBase::allChildren(QObject *papi)
{
	QObjectList rtn;
	if( papi )
	{
		foreach( QObject *ob, papi->children() )
		{
			rtn += ob;
			rtn += allChildren(ob);
		}
	}
	return rtn;
}

void QDialogBase::setReadOnly(bool readOnly)
{
	foreach( QObject *ob, allChildren(this) )
	{
		if( qobject_cast<QLineEdit*>(ob) != Q_NULLPTR )
			qobject_cast<QLineEdit*>(ob)->setReadOnly(readOnly);
		else
		if( qobject_cast<QSpinBox*>(ob) != Q_NULLPTR )
			qobject_cast<QSpinBox*>(ob)->setReadOnly(readOnly);
		else
		if( qobject_cast<QComboBox*>(ob) != Q_NULLPTR )
			qobject_cast<QComboBox*>(ob)->setDisabled(readOnly);
		else
		if( qobject_cast<QTableView*>(ob) != Q_NULLPTR )
			qobject_cast<QTableView*>(ob)->setDisabled(readOnly);
		else
		if( qobject_cast<QListView*>(ob) != Q_NULLPTR )
			qobject_cast<QListView*>(ob)->setDisabled(readOnly);
		else
		if( qobject_cast<QTreeView*>(ob) != Q_NULLPTR )
			qobject_cast<QTreeView*>(ob)->setDisabled(readOnly);
		else
		if( qobject_cast<QAbstractButton*>(ob) != Q_NULLPTR )
			qobject_cast<QAbstractButton*>(ob)->setDisabled(readOnly);
	}
}

bool QNewROSDataDialogBase::exec(ROSDataBase &rosData)
{
	setROSData(rosData);
	if( QDialog::exec() == QDialog::Accepted )
	{
		if( getROSData(rosData) )
			return true;
	}
	return false;
}

void QDlgMultiDataBase::updateMultipleData(DataTypeIDList dataTypeIDList, const QString &routerName)
{
	Q_ASSERT( children().count() );		// This function must be called when ui has been configured.

	m_dataTypeIDList = dataTypeIDList;
	foreach( DataTypeID dataTypeID, m_dataTypeIDList )
	{
		ROSDataBasePList dataList = m_rosMultiConnectManager.rosDataList(dataTypeID, routerName);
		if( dataList.count() )
		{
			foreach( const ROSDataBase *rosData, dataList )
				onROSModReply( *rosData );
		}
		else
			m_rosMultiConnectManager.requestAll(dataTypeID);
	}
}

QDlgMultiDataBase::QDlgMultiDataBase(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent)
	: QDialogBase(parent)
  , m_configData(configData)
  , m_rosMultiConnectManager(rosMultiConnectManager)
{

}

void QDlgMultiDataBase::onLogued(const QString &routerName)
{
	updateMultipleData(m_dataTypeIDList, routerName);
}

void QDlgMultiDataBase::onDisconnected(const QString &routerName)
{
	foreach( DataTypeID dataTypeID, m_dataTypeIDList )
		onROSDelReply( routerName, dataTypeID, QString() );
}
