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

#include "QROSSecretTableWidget.h"

#include <QMenu>
#include <QDesktopServices>
#include <QFont>
#include <QHeaderView>
#include <QMessageBox>

#include "../Utils/Utils.h"
#include "../ConfigData/QConfigData.h"
#include "../ConfigData/ClientProfile.h"
#include "../ROSMultiConnectorManager.h"

#include "QRemoteIPCellItem.h"

#include "QComboBoxItemDelegate.h"

void QStyledWidgetItem::updateStyle()
{
	m_cellLook = getCellLook();
	QFont font = this->font();
	font.setItalic( m_cellLook.m_fontItalic );
	font.setBold( m_cellLook.m_fontBold );
	font.setFamily( m_cellLook.m_fontFamily );
	setFont( font );
	setForeground( QBrush(m_cellLook.m_foreColor) );
	setBackground( QBrush(m_cellLook.m_backColor) );
}

const CellLook &QROSServiceStatusCellItem::getCellLook()
{
	switch( m_serviceState )
	{
	case ServiceState::ActiveUndefined:		return gGlobalConfig.tableCellLook().m_enabled;
	case ServiceState::ActiveTemporally:	return gGlobalConfig.tableCellLook().m_enabled;
	case ServiceState::CanceledNoPay:		return gGlobalConfig.tableCellLook().m_disabledNoPay;
	case ServiceState::CanceledTemporally:	return gGlobalConfig.tableCellLook().m_disabledTemporary;
	case ServiceState::CanceledTechnically:	return gGlobalConfig.tableCellLook().m_disabledTechnically;
	case ServiceState::CanceledNoRetired:	return gGlobalConfig.tableCellLook().m_disabledDevicesNoRetired;
	case ServiceState::CanceledRetired:		return gGlobalConfig.tableCellLook().m_disabledDevicesRetired;
	case ServiceState::CanceledUndefined:	return gGlobalConfig.tableCellLook().m_disabledUndefined;
	case ServiceState::Undefined:           Q_ASSERT( false );
	}
	Q_ASSERT(false);
	return gGlobalConfig.tableCellLook().m_enabled;
}

void QROSActiveStatusCellItem::updateText()
{
	if( curUpTime.isValid() )
		setText( QString("C: %1").arg(curUpTime.toString("yyyy/MM/dd hh:mm:ss")) );
	else
		setText( QString("D: %1").arg(curDwTime.toString("yyyy/MM/dd hh:mm:ss")) );
}

const CellLook &QROSActiveStatusCellItem::getCellLook()
{
	if( curUpTime.isValid() )
		return gGlobalConfig.tableCellLook().m_connected;
	return gGlobalConfig.tableCellLook().m_disconnected;
}

QStringList QROSSecretTableWidget::columnsNames()
{
	static QStringList rtn;
	if( rtn.isEmpty() )
	{
		rtn = QStringList()
				<< tr("Usuario")
				<< tr("CCliente")
				<< tr("Servicio")
				<< tr("Perfil")
				<< tr("Estado")
				<< tr("IP")
				<< tr("Router")
				<< tr("Nombre")
				<< tr("Dirección")
				<< tr("Población")
				<< tr("Teléfonos")
				<< tr("Instalador")
				<< tr("Email")
				<< tr("Notas Cliente")
				<< tr("Notas Instalación") ;
		Q_ASSERT( rtn.count() == TotalColumns );
	}
	return rtn;
}

void QROSSecretTableWidget::setColumnHidden(int col, bool hidden)
{
	QTableWidget::setColumnHidden(col, hidden);
	if( hidden )
	{
		if( !gGlobalConfig.columnsHidden().contains(col) )
			gGlobalConfig.columnsHidden().append(col);
	}
	else
		gGlobalConfig.columnsHidden().removeAll(col);
}

QROSSecretTableWidget::QROSSecretTableWidget(QWidget *papi)
	: QTableWidget(papi)
	, m_filterServiceState( static_cast<ServiceState::Type>(-3))
{
	setColumnCount( columnsNames().count() );
	setHorizontalHeaderLabels( columnsNames() );

	setItemDelegate( new QLineEditItemDelegated( this,
												 [this] (const QModelIndex &index,const QString &newText)	{ return allowCellChange(index, newText); } ) );

	setItemDelegateForColumn( Columns::UserProfile,
							  new QComboBoxItemDelegated( this, "", "", false,
		/*add list*/			  [] (int)			{ return gGlobalConfig.clientProfileMap().regularProfileNames();	},
		/*skip list*/			  [] (int)			{ return QStringList(); },
		/*allow change*/		  [this] (const QModelIndex &index,const QString &newText)	{ return allowCellChange(index, newText); } ) );

	setItemDelegateForColumn( Columns::RemoteIP,
							  new QComboBoxItemDelegated( this, tr("IP dinámica"), "", false,
								  [this] (int row)	{ return staticIPs(row); },
								  [this] (int)		{ return usedStaticIPs(); },
		/*allow change*/		  [this] (const QModelIndex &index,const QString &newText)	{ return allowCellChange(index, newText); },
		/*initial text*/		  [this] (const QModelIndex &index)	{ return currentIP(index.row()); } ) );

	setItemDelegateForColumn( Columns::Installer,
							  new QComboBoxItemDelegated( this, gGlobalConfig.userName(), gGlobalConfig.userName(), false,
								  [] (int)			{ return gGlobalConfig.instaladores(); },
								  [] (int)			{ return QStringList(); },
		/*allow change*/		  [this] (const QModelIndex &index,const QString &newText)	{ return allowCellChange(index, newText); } ) );

	setItemDelegateForColumn( Columns::ServiceStatus,
							  new QComboBoxItemDelegated( this, "", "", false,
								  [] (int)			{ return ServiceState::serviceStateNameList(); },
								  [] (int)			{ return QStringList(); },
		/*allow change*/		  [this] (const QModelIndex &index,const QString &newText)	{ return allowCellChange(index, newText); } ) );

	setSortingEnabled(true);
	horizontalHeader()->setSectionsMovable(true);
//	horizontalHeader()->saveState();
	connect( this, &QROSSecretTableWidget::itemDoubleClicked, this, &QROSSecretTableWidget::onCellDobleClic );
}

QList<int> QROSSecretTableWidget::findData(const QString &text, QList<Columns> columns, bool exactMatch)
{
	QList<int> rtn;
	for( int row = rowCount()-1; row >= 0; --row )
	{
		foreach( Columns col, columns )
		{
			if( item(row, col) )
			{
				if( (exactMatch && (item(row, col)->text() == text)) ||
					(!exactMatch && item(row, col)->text().contains(text)) )
				rtn.append(row);
			}
		}
	}
	return rtn;
}

bool QROSSecretTableWidget::shouldBeVisible(const QROSUserNameWidgetItem *userNameItem)
{
	if( !userNameItem || userNameItem->pppSecretMap.isEmpty() )
		return false;
	const ROSPPPSecret &rosPPPSecret = userNameItem->pppSecretMap.first();
	if( gGlobalConfig.clientProfileMap().containsProfileName(rosPPPSecret.pppProfileName()) )
	{
		switch( static_cast<int>(m_filterServiceState) )
		{
		case -3:	// Meaning: All cases.
			break;
		case -2:	// Meaning Active only.
			if( ServiceState::isCanceledState(rosPPPSecret.serviceState()) )
				return false;
			break;
		case -1:	// Meaning inactives only.
			if( !ServiceState::isCanceledState(rosPPPSecret.serviceState()) )
				return false;
			break;
		default:
			if( rosPPPSecret.serviceState() != m_filterServiceState )
				return false;
			break;
		}
		if( !m_filterText.isEmpty() )
		{
			// Meaning: search on all fields.
			if( static_cast<int>(m_filterFields) == -2 )
				return	rosPPPSecret.userName().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.clientName().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.clientAddress().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.clientCity().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.clientPhones().contains(m_filterText) ||
						rosPPPSecret.clientCode().contains(m_filterText) ||
						rosPPPSecret.clientEmail().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.clientNotes().contains(m_filterText, Qt::CaseInsensitive) ||
						rosPPPSecret.installNotes().contains(m_filterText, Qt::CaseInsensitive);

			// Meaning: Multiple user names.
			if( static_cast<int>(m_filterFields) == -1 )
				return m_filterText.contains(rosPPPSecret.userName(), Qt::CaseInsensitive);

			switch( m_filterFields )
			{
			case QROSSecretTableWidget::UserName:			return rosPPPSecret.userName().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientCode:			return rosPPPSecret.clientCode().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ServiceStatus:		return ServiceState::readableString(rosPPPSecret.serviceState()).contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::UserProfile:		return rosPPPSecret.originalProfile().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ActiveRouter:		return userNameItem->pppActive.routerName().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ActiveUserStatus:	return true;	// TODO: Maybe a date filter could be fine.
			case QROSSecretTableWidget::RemoteIP:			return userNameItem->pppActive.currentIPv4().toString().startsWith(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientName:			return rosPPPSecret.clientName().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientAddress:		return rosPPPSecret.clientAddress().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientCity:			return rosPPPSecret.clientCity().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientPhone:		return rosPPPSecret.clientPhones().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::Installer:			return rosPPPSecret.installerName().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientEmail:		return rosPPPSecret.clientEmail().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::ClientAnnotations:	return rosPPPSecret.clientNotes().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::InstallAnnotations:	return rosPPPSecret.installNotes().contains(m_filterText, Qt::CaseInsensitive);
			case QROSSecretTableWidget::TotalColumns:
				break;
			}
		}
		return true;
	}
	return false;
}

void QROSSecretTableWidget::showRowIfValid(const QROSUserNameWidgetItem *userNameItem)
{
	shouldBeVisible(userNameItem) ? showRow(userNameItem->row()) : hideRow(userNameItem->row());
}

void QROSSecretTableWidget::raiseWarning(const QString &info) const
{
	QMessageBox::warning( const_cast<QROSSecretTableWidget*>(this), tr("Datos usuario"), info );
}

bool QROSSecretTableWidget::checkStringData(ROSPPPSecret &pppSecret, const QString &fieldName, const QString &text, std::function<bool (ROSPPPSecret &, const QString &)> setFnc) const
{
	if( !setFnc(pppSecret, text) )
	{
		raiseWarning( tr("%1, %2").arg(fieldName, pppSecret.lastError()) );
		return false;
	}
	return true;
}

void QROSSecretTableWidget::applyFilter()
{
	for( int row = rowCount()-1; row >= 0; --row )
		showRowIfValid( userNameWidgetItem(row) );
}

void QROSSecretTableWidget::changeUserProfile(QROSUserNameWidgetItem *userNameItem, const QString &newProfile)
{
	if( userNameItem && userNameItem->pppSecretMap.count() )
	{
		ROSPPPSecret secret = userNameItem->pppSecretMap.first();

		if( !ServiceState::isCanceledState(secret.serviceState()) )
			secret.setPPPProfileName( newProfile );
		secret.setOriginalProfile( newProfile );

		multiConnectionManager.updateRemoteData( secret, userNameItem->pppSecretMap.toRouterIDMap() );

		disconnectUser(userNameItem->row());
	}
}

void QROSSecretTableWidget::changeMultipleProfiles(const QList<QROSUserNameWidgetItem *> &selectedList, const QString newProfile)
{
	for( QROSUserNameWidgetItem *userNameWidgetItem : selectedList )
		changeUserProfile(userNameWidgetItem, newProfile);
}

void QROSSecretTableWidget::openThroughputDialog(int row)
{
	QROSUserNameWidgetItem *userNameItem = userNameWidgetItem(row);
	emit showUserTraffic( userNameItem->pppSecretMap, userNameItem->pppActive );
}

QString QROSSecretTableWidget::cellText(int row, QROSSecretTableWidget::Columns col) const
{
	Q_ASSERT(row >= 0);
	Q_ASSERT(row < rowCount());
	Q_ASSERT(col >= 0);
	Q_ASSERT(col < columnCount() );
	return item(row, col) ? item(row, col)->text() : QString();
}

void QROSSecretTableWidget::setupCellItemStyle(QTableWidgetItem *item, const CellLook &cellLook)
{
	QFont font = item->font();
	font.setItalic( cellLook.m_fontItalic );
	font.setBold( cellLook.m_fontBold );
	font.setFamily( cellLook.m_fontFamily );
	item->setFont( font );
	item->setForeground( QBrush(cellLook.m_foreColor) );
	item->setBackground( QBrush(cellLook.m_backColor) );
}

void QROSSecretTableWidget::setupCellItemStyle(int row, QROSSecretTableWidget::Columns col, const CellLook &cellLook)
{
	QTableWidgetItem *item = this->item(row, col);
	if( item != Q_NULLPTR )
		QROSSecretTableWidget::setupCellItemStyle(item, cellLook);
}

void QROSSecretTableWidget::clear()
{
	setRowCount(0);
	m_activeIDMap.clear();
	m_secretIDMap.clear();
	m_userNameMap.clear();
	m_usedStaticIPList.clear();
}

QString QROSSecretTableWidget::createObjectIDKey(const ROSPPPSecret &rosPPPSecret)
{
	return createObjectIDKey(rosPPPSecret.routerName(), rosPPPSecret.rosObjectID());
}
QString QROSSecretTableWidget::createObjectIDKey(const QString &routerName, const QString &rosObjectID)
{
	return QString("%1:%2").arg(routerName, rosObjectID);
}

QList<QROSUserNameWidgetItem *> QROSSecretTableWidget::selectedUsers()
{
	QList<QROSUserNameWidgetItem*> userNameItemList;
	foreach( const QModelIndex &index, selectedIndexes() )
	{
		if( !userNameItemList.contains(userNameWidgetItem(index.row())) )
			userNameItemList.append(userNameWidgetItem(index.row()));
	}
	return userNameItemList;
}

void QROSSecretTableWidget::setupCellItem(int row, Columns col, const QString &cellText, bool editable)
{
	if( item(row, col) == Q_NULLPTR )
	{
		setItem(row, col, new QTableWidgetItem(cellText));
		if( !editable )
			item( row, col)->setFlags(item(row, col)->flags() & ~Qt::ItemIsEditable);
	}
	else
		item(row, col)->setText(cellText);
}

void QROSSecretTableWidget::setupServiceCellItem(int row, ServiceState::Type st)
{
	if( item(row, Columns::ServiceStatus) == Q_NULLPTR )
		setItem(row, Columns::ServiceStatus, new QROSServiceStatusCellItem());
	static_cast<QROSServiceStatusCellItem*>(item(row, Columns::ServiceStatus))->setServiceState(st);
}

QROSActiveStatusCellItem*QROSSecretTableWidget::setupActiveStatusCellItem(int row)
{
	QROSActiveStatusCellItem *rtn;
	if( (rtn = static_cast<QROSActiveStatusCellItem*>(item(row, Columns::ActiveUserStatus))) == Q_NULLPTR )
	{
		setItem( row, Columns::ActiveUserStatus, rtn = new QROSActiveStatusCellItem() );
		rtn->setFlags(item(row, Columns::ActiveUserStatus)->flags() & ~Qt::ItemIsEditable);
	}
	return rtn;
}

void QROSSecretTableWidget::setupRemoteIPCellItem(int row, const IPv4 &remoteIP, const IPv4 &staticIP)
{
	if( item(row, Columns::RemoteIP) == Q_NULLPTR )
		setItem(row, Columns::RemoteIP, new QRemoteIPCellItem(remoteIP, staticIP));
	else
		static_cast<QRemoteIPCellItem*>(item(row, Columns::RemoteIP))->setRemoteIPs(remoteIP, staticIP);
}

void QROSSecretTableWidget::setupRemoteIPCellItem(const QROSUserNameWidgetItem *userNameItem)
{
	setupRemoteIPCellItem( userNameItem->row(), userNameItem->pppActive.currentIPv4(), userNameItem->pppSecretMap.isEmpty() ? IPv4() : userNameItem->pppSecretMap.first().staticIP() );
}

QROSUserNameWidgetItem *QROSSecretTableWidget::addNewRow(const QString &userName)
{
	int row = rowCount();

	insertRow(row);
	// All right, there is no item. Let's create a new one.
	QROSUserNameWidgetItem *userNameItem = new QROSUserNameWidgetItem();
	// Put it on user name column.
	setItem(row, Columns::UserName, userNameItem);
	item(row, Columns::UserName)->setFlags(item(row, Columns::UserName)->flags() & ~Qt::ItemIsEditable);
	userNameItem->setText( userName );

	m_userNameMap[userName] = userNameItem;
	return userNameItem;
}

QROSUserNameWidgetItem *QROSSecretTableWidget::userNameWidgetItem(int row)
{
	return static_cast<QROSUserNameWidgetItem*>(item(row, Columns::UserName));
}

const QROSUserNameWidgetItem *QROSSecretTableWidget::userNameWidgetItem(int row) const
{
	return static_cast<const QROSUserNameWidgetItem*>(item(row, Columns::UserName));
}

void QROSSecretTableWidget::onROSSecretModReply(const ROSPPPSecret &pppSecret)
{
	if( pppSecret.pppProfileName().isEmpty() )
		return;

	blockSignals(true);

	QROSUserNameWidgetItem *userNameItem;

	// Find the item by the pair routerName-rosObjectID (the ObjectIDKey)...
	if( (userNameItem = m_secretIDMap.value(createObjectIDKey(pppSecret), Q_NULLPTR)) == Q_NULLPTR )
	{
		// ...or by the name if it was created before by the a secretActive event.
		if( (userNameItem = m_userNameMap.value(pppSecret.userName(), Q_NULLPTR)) == Q_NULLPTR )
			userNameItem = addNewRow(pppSecret.userName());

//		userNameItem->rosCachedPPPSecret = rosPPPSecret;
		m_secretIDMap[createObjectIDKey(pppSecret)] = userNameItem;
	}
	userNameItem->pppSecretMap.insert( pppSecret );

	// As username is key for this map, has special code.
	if( item(userNameItem->row(), Columns::UserName)->text() != pppSecret.userName() )
	{
		// Copy the item to the new name key.
		m_userNameMap[pppSecret.userName()] = m_userNameMap.take( item(userNameItem->row(), Columns::UserName)->text() );
		setupCellItem(userNameItem->row(), UserName,				pppSecret.userName(), false );
	}

	setupCellItem( userNameItem->row(), Columns::ClientCode,		pppSecret.clientCode(), true );
	setupCellItem( userNameItem->row(), Columns::UserProfile,		pppSecret.originalProfile(), true );
	setupCellItem( userNameItem->row(), Columns::ClientName,		pppSecret.clientName(), true );
	setupCellItem( userNameItem->row(), Columns::ClientAddress,		pppSecret.clientAddress(), true );
	setupCellItem( userNameItem->row(), Columns::ClientCity,		pppSecret.clientCity(), true );
	setupCellItem( userNameItem->row(), Columns::ClientPhone,		pppSecret.clientPhones(), true );
	setupCellItem( userNameItem->row(), Columns::Installer,			pppSecret.installerName(), true );
	setupCellItem( userNameItem->row(), Columns::ClientEmail,		pppSecret.clientEmail(), true );
	setupCellItem( userNameItem->row(), Columns::ClientAnnotations,	pppSecret.clientNotes(), true );
	setupCellItem( userNameItem->row(), Columns::InstallAnnotations,pppSecret.installNotes(), true );

	// This columns can be filled by active data before the secred was reported. So, here will set data only if they're empty.
	// TODO: Last logg off must show the last (date-nearest) value because every router will has diferent time-stamp.
	//       Maybe, could be interesting also keep all data and show to user via cell tool-tip
	setupActiveStatusCellItem( userNameItem->row() )->setLastDowntime( pppSecret.routerName(), pppSecret.lastLogOff() );

	if( item(userNameItem->row(), Columns::ActiveRouter) == Q_NULLPTR )
		setupCellItem( userNameItem->row(), Columns::ActiveRouter,	tr("Ninguno"), false );

	setupRemoteIPCellItem( userNameItem );
	if( pppSecret.serviceState() == ServiceState::Undefined )
	{
		if( gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName() == pppSecret.pppProfileName() )
			setupServiceCellItem( userNameItem->row(), ServiceState::CanceledUndefined );
		else
			setupServiceCellItem( userNameItem->row(), ServiceState::ActiveUndefined );
	}
	else
	{
		setupServiceCellItem( userNameItem->row(), pppSecret.serviceState() );
	}
	showRowIfValid( userNameItem );

	blockSignals(false);
}

void QROSSecretTableWidget::onROSSecretDelReply(const QString &routerName, const QString &rosObjectID)
{
	QString key = createObjectIDKey(routerName, rosObjectID);
	QROSUserNameWidgetItem *userNameItem = m_secretIDMap.value(key, Q_NULLPTR);

	if( userNameItem != Q_NULLPTR )
	{
		userNameItem->pppSecretMap.remove( routerName );
		if( userNameItem->pppSecretMap.isEmpty() )
		{
			m_userNameMap.remove( userNameItem->text() );
			m_secretIDMap.remove( key );
			m_activeIDMap.remove( userNameItem->pppActive.rosObjectID() );
			blockSignals(true);
			removeRow(userNameItem->row());
			blockSignals(false);
		}
	}
}

void QROSSecretTableWidget::onROSActiveModReply(const ROSPPPActive &rosPPPActive)
{
	QROSUserNameWidgetItem *userNameItem = m_userNameMap.value( rosPPPActive.userName(), Q_NULLPTR );

	blockSignals(true);
	// If there is nothing here, could be a active event before the secred has arrived.
	if( userNameItem == Q_NULLPTR )
		userNameItem = addNewRow(rosPPPActive.userName());

	// That could happen when a new connection comes before a desconnection.
	if( !userNameItem->pppActive.rosObjectID().isEmpty() )
		m_activeIDMap.remove(userNameItem->pppActive.rosObjectID());

	userNameItem->pppActive = rosPPPActive;

	m_activeIDMap[rosPPPActive.rosObjectID()] = userNameItem;

	setupActiveStatusCellItem( userNameItem->row() )->setUptime( rosPPPActive.routerName(), rosPPPActive.uptime() );
	setupRemoteIPCellItem( userNameItem );
	setupCellItem( userNameItem->row(), Columns::ActiveRouter, rosPPPActive.routerName(), false );
	blockSignals(false);
}

void QROSSecretTableWidget::onROSActiveDelReply(const QString &routerName, const QString &rosObjectID)
{
	QROSUserNameWidgetItem *userNameItem = m_activeIDMap.value(rosObjectID, Q_NULLPTR);

	// Not found: not yet in table.
	if( userNameItem != Q_NULLPTR )
	{
		userNameItem->pppActive = ROSPPPActive("");
		// Take care. can be a connection from another router.
		if( item(userNameItem->row(), Columns::ActiveRouter)->text() == routerName )
		{
			blockSignals(true);
			setupActiveStatusCellItem( userNameItem->row() )->setCurrentDowntime( routerName, QDateTime::currentDateTime() );
			setupCellItem( userNameItem->row(), Columns::ActiveRouter, tr("Ninguno"), false );
			setupRemoteIPCellItem( userNameItem );
			m_activeIDMap.remove(rosObjectID);
			blockSignals(false);
		}
	}
}

void QROSSecretTableWidget::onROSModReply(const ROSDataBase &rosData)
{
	if( rosData.dataTypeID() == DataTypeID::PPPSecret )
		onROSSecretModReply( static_cast<const ROSPPPSecret &>(rosData) );
	else
	if( rosData.dataTypeID() == DataTypeID::PPPActive )
		onROSActiveModReply( static_cast<const ROSPPPActive &>(rosData) );
}

void QROSSecretTableWidget::onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID)
{
	if( dataTypeID == DataTypeID::PPPSecret )
		onROSSecretDelReply(routerName, rosObjectID);
	else
	if( dataTypeID == DataTypeID::PPPActive )
		onROSActiveDelReply(routerName, rosObjectID);
}

void QROSSecretTableWidget::onROSDone(const QString &routerName, DataTypeID dataTypeID)
{
	Q_UNUSED(routerName);
	if( (dataTypeID == DataTypeID::PPPSecret) || (dataTypeID == DataTypeID::PPPActive) )
		resizeColumnsToContents();
}

void QROSSecretTableWidget::onConfigChanged()
{
	QFont tableFont = font();
	tableFont.setPixelSize( gGlobalConfig.tableCellLook().m_fontSize );
	setFont( tableFont );
	verticalHeader()->setDefaultSectionSize( gGlobalConfig.tableCellLook().m_rowHeight );

	foreach( int col, gGlobalConfig.columnsHidden() )
		QTableWidget::setColumnHidden(col, true);

	for( int row = rowCount()-1; row >= 0; --row )
	{
		for( int col = columnCount()-1; col >=0; --col )
		{
			if( dynamic_cast<QStyledWidgetItem*>(item(row, static_cast<Columns>(col))) != Q_NULLPTR )
			{
				static_cast<QStyledWidgetItem*>(item(row, static_cast<Columns>(col)))->updateStyle();
			}
		}
	}
}

QString QROSSecretTableWidget::currentIP(int row)
{
	if( item(row, Columns::RemoteIP) )
	{
		Q_ASSERT( static_cast<QRemoteIPCellItem*>(item(row, Columns::RemoteIP)) );
		if( static_cast<QRemoteIPCellItem*>(item(row, Columns::RemoteIP))->staticIP().isValid() )
			return static_cast<QRemoteIPCellItem*>(item(row, Columns::RemoteIP))->staticIP().toString();
	}
	return QString();
}

void QROSSecretTableWidget::filter(const QString &text, Columns col, ServiceState::Type filterStates)
{
	m_filterText = text;
	m_filterFields = col;
	m_filterServiceState = filterStates;
	applyFilter();
}

QStringList QROSSecretTableWidget::usedStaticIPs() const
{
	QStringList rtn;

	for( int row = rowCount(); row >= 0; --row )
	{
		if( static_cast<const QRemoteIPCellItem*>(item(row, Columns::RemoteIP)) && static_cast<const QRemoteIPCellItem*>(item(row, Columns::RemoteIP))->staticIP().isValid() )
			rtn.append(static_cast<const QRemoteIPCellItem*>(item(row, Columns::RemoteIP))->staticIP().toString() );
	}
	return rtn;
}

QStringList QROSSecretTableWidget::staticIPs(int row) const
{
	QString clientProfileName = item(row, Columns::UserProfile)->text();
	QString clientProfileGroup = gGlobalConfig.clientProfileMap().groupName(clientProfileName);
	return gGlobalConfig.staticIPv4RangeListMap().staticIPv4StringList(clientProfileGroup);
}

bool QROSSecretTableWidget::allowCellChange(const QModelIndex &index, const QString &newText)
{
	if( (gGlobalConfig.userLevel() <= ROSAPIUser::Level::Comercial) )
		return false;

	QROSUserNameWidgetItem *userNameItem = userNameWidgetItem(index.row());
	Q_ASSERT(userNameItem);
	ROSPPPSecret newSecret = userNameItem->pppSecretMap.first();

	std::function<bool(ROSPPPSecret &, const QString &)> setFnc;
	QString fieldName;
	bool needReconect = false;

	if( userNameItem )
	{
		switch( static_cast<Columns>(index.column()) )
		{
		case QROSSecretTableWidget::UserName:
			Q_ASSERT(false);
			break;
		case QROSSecretTableWidget::ClientCode:
			if( gGlobalConfig.userLevel() >= ROSAPIUser::Level::Administrator )
			{
				QStringList duplicatedClients;
				for( int row = rowCount()-1; row >= 0; --row )
				{
					if( (row != index.row()) && (item(row, Columns::ClientCode)->text() == newText) )
						duplicatedClients.append( QString("%1 (%2)").arg(item(row, Columns::UserName)->text(), item(row, Columns::ClientName)->text()) );
				}
				if( duplicatedClients.count() )
				{
					if( QMessageBox::question(this, tr("Código de cliente"), tr("El código de cliente %1 que pones para %2 (%3) también está asociado a:\n%4\n\n¿Es correcto?")
											.arg(newText)
											.arg(item(index.row(), Columns::UserName)->text(), item(index.row(), Columns::ClientName)->text())
											.arg(duplicatedClients.join('\n')),
										  QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes )
						return false;
				}
				fieldName = tr("Código de cliente");
				setFnc = &ROSPPPSecret::setClientCode;
			}
			break;
		case QROSSecretTableWidget::ServiceStatus: 			// This is not a string, so cannot be set by setFnc
			if( (gGlobalConfig.userLevel() == ROSAPIUser::Level::Administrator) ||
				(gGlobalConfig.userLevel() == ROSAPIUser::Level::Supervisor) )
			{
				newSecret.setServiceState( ServiceState::fromNameString(newText) );
				if( !ServiceState::isCanceledState(newSecret.serviceState()) && (newSecret.pppProfileName() == gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName()) )
					newSecret.setPPPProfileName( newSecret.originalProfile() );
				else
				if( ServiceState::isCanceledState(newSecret.serviceState()) && (newSecret.pppProfileName() != gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName()) )
					newSecret.setPPPProfileName( gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName() );
				multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
				needReconect = true;
			}
			break;
		case QROSSecretTableWidget::UserProfile: // This is a special case where maybe two fields changes at once.
			if( !ServiceState::isCanceledState(newSecret.serviceState()) )
				newSecret.setPPPProfileName( newText );
			newSecret.setOriginalProfile( newText );
			needReconect = true;
			multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
			break;
		case QROSSecretTableWidget::ActiveUserStatus:
			Q_ASSERT(false);
			break;
		case QROSSecretTableWidget::ActiveRouter:
			Q_ASSERT(false);
			break;
		case QROSSecretTableWidget::RemoteIP:
			// This is not a string, so cannot be set by setFnc
			newSecret.setStaticIP( IPv4(newText) );
			multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
			needReconect = true;
			break;
		case QROSSecretTableWidget::ClientName:
			fieldName = tr("Nombre del cliente");
			setFnc = &ROSPPPSecret::setClientName;
			break;
		case QROSSecretTableWidget::ClientAddress:
			fieldName = tr("Dirección del cliente");
			setFnc = &ROSPPPSecret::setClientAddress;
			break;
		case QROSSecretTableWidget::ClientCity:
			fieldName = tr("Población del cliente");
			setFnc = &ROSPPPSecret::setClientCity;
			break;
		case QROSSecretTableWidget::ClientPhone:
			fieldName = tr("Teléfonos de contacto del cliente");
			setFnc = &ROSPPPSecret::setClientPhones;
			break;
		case QROSSecretTableWidget::Installer:
			fieldName = tr("Nombre del técnico que hizo la instalación");
			setFnc = &ROSPPPSecret::setInstallerName;
			break;
		case QROSSecretTableWidget::ClientEmail:
			fieldName = tr("Dirección de correo electónico del cliente");
			setFnc = &ROSPPPSecret::setClientEmail;
			break;
		case QROSSecretTableWidget::ClientAnnotations:
			fieldName = tr("Notas sobre el cliente");
			setFnc = &ROSPPPSecret::setClientNotes;
			break;
		case QROSSecretTableWidget::InstallAnnotations:
			fieldName = tr("Notas sobre la instalación");
			setFnc = &ROSPPPSecret::setInstallNotes;
			break;
		case QROSSecretTableWidget::TotalColumns:
			Q_ASSERT(false);
			break;
		}
	}

	if( !fieldName.isEmpty() && checkStringData(newSecret, fieldName, newText, setFnc) )
		multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
	if( needReconect )
		disconnectUser(userNameItem->row());
	return false;
}

void QROSSecretTableWidget::disconnectUser(int row)
{
	ROSPPPActive &rosActive = userNameWidgetItem(row)->pppActive;
	if( !rosActive.rosObjectID().isEmpty() && !rosActive.deleting() )
	{
		rosActive.setDeleting(true);
		multiConnectionManager.updateRemoteData(rosActive);
	}
}

void QROSSecretTableWidget::disconnectSelected()
{
	foreach( const QModelIndex &index, selectedIndexes() )
		disconnectUser(index.row());
}

void QROSSecretTableWidget::deleteUser(const QString &userName, bool sure) const
{
	const QROSUserNameWidgetItem *item = m_userNameMap[userName];
	if( item != Q_NULLPTR )
	{
		ROSPPPSecret pppSecret = item->pppSecretMap.first();
		pppSecret.setDeleting(true);
		if( !sure )
		{
			if( QMessageBox::warning( const_cast<QROSSecretTableWidget*>(this), parent()->objectName(), tr("¿Seguro que quieres borrar al usuario %1?").arg(userName), QMessageBox::No | QMessageBox::Yes ) == QMessageBox::Yes )
				deleteUser(userName, true);
		}
		else
			multiConnectionManager.updateRemoteData( pppSecret, item->pppSecretMap.toRouterIDMap() );
	}
}

void QROSSecretTableWidget::onCellDobleClic(QTableWidgetItem *item)
{
	if( item->column() == static_cast<int>(Columns::UserName) )
	{
		QROSUserNameWidgetItem *userNameItem = static_cast<QROSUserNameWidgetItem*>(item);
		emit editPPPUser( userNameItem->pppSecretMap, userNameItem->pppActive );
	}
}

void QROSSecretTableWidget::onConfigDataChanged()
{
	applyFilter();
}

const ROSPPPSecret *QROSSecretTableWidget::rosPppSecret(const QString &userName)
{
	const QROSUserNameWidgetItem *item = m_userNameMap[userName];

	return (item != Q_NULLPTR) ? &item->pppSecretMap.first() : Q_NULLPTR;
}

#include "Dialogs/DlgExportUserData.h"
void QROSSecretTableWidget::exportUsersData()
{
	QList<QStringList> exportData;
	QList<QROSUserNameWidgetItem*> selectedList = selectedUsers();
	QStringList data;
	if( selectedList.count() )
	{
		foreach( QROSUserNameWidgetItem *item, selectedList )
		{
			data.clear();
			for( int col = 0; col < columnCount(); ++col )
			{
				if( !isColumnHidden(col) )
					data.append(QTableWidget::item(item->row(), col)->text());
			}
			exportData.append(data);
		}
	}
	else
	{
		for( int row = 0; row < rowCount(); ++row )
		{
			data.clear();
			for( int col = 0; col < columnCount(); ++col )
			{
				if( !isColumnHidden(col) )
					data.append(QTableWidget::item(row, col)->text());
			}
			exportData.append(data);
		}
	}
	if( exportData.count() )
		DlgExportUserData::exportData(exportData, this);
}

void QROSSecretTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QAction *ac;
	QList<QROSUserNameWidgetItem*> selectedList = selectedUsers();
	QList<QROSUserNameWidgetItem*> connectedList;
	for( QROSUserNameWidgetItem *userNameItem : selectedList )
	{
		if( userNameItem->pppActive.currentIPv4().isValid() && !connectedList.contains(userNameItem) )
			connectedList.append( userNameItem );
	}
	QMenu rootMenu(this);
	QMenu chngProfileSubmenu( tr("Cambiar perfil") ) ;
	QMenu openBrowserSubMenu( tr("Abrir navegador") ) ;
	QMenu columnsSubmenu( tr("Columnas") );

	if( gGlobalConfig.userLevel() >= ROSAPIUser::Level::Instalator )
	{
		if( !connectedList.isEmpty() )
		{
			QString txt;
			if( connectedList.count() == 1 )
				txt = tr("Forzar reconexión cliente %1").arg(connectedList.first()->pppActive.userName());
			else
				txt = tr("Forzar reconexión %1 clientes").arg(connectedList.count());
			connect( rootMenu.addAction(txt), &QAction::triggered, this, &QROSSecretTableWidget::disconnectSelected );
		}
	}

	for( const QROSUserNameWidgetItem *userNameItem : connectedList )
	{
		const ROSPPPActive &rosActive = userNameItem->pppActive;
		if( rosActive.currentIPv4().isValid() )
		{
			int row = userNameItem->row();
			connect( rootMenu.addAction( tr("Ver consumo en directo de %1").arg(rosActive.userName())), &QAction::triggered,
					 [this, row] { QROSSecretTableWidget::openThroughputDialog(row); } );
			openBrowserSubMenu.setTitle( tr("Abrir web %1 ...").arg(rosActive.currentIPv4().toString()) );

			OpenBrowserInfoList obl(userNameItem->pppSecretMap.first().portForwardList());
			obl += gGlobalConfig.openBrowserInfoList();

			foreach( OpenBrowserInfo obf, obl )
			{
				obf.ip = rosActive.currentIPv4().toString();
				QString url = obf.toURL();
				QAction *ac = openBrowserSubMenu.addAction( QString("puerto %1 (%2)").arg(obf.port, obf.name) );
				connect( ac, &QAction::triggered, [url] () { QDesktopServices::openUrl( QUrl(url) ); } );
			}
			rootMenu.addMenu( &openBrowserSubMenu );
			break;
		}
	}

	QStringList columnNames = columnsNames();
	for( int col = 0; col < columnNames.count(); ++col )
	{
		ac = columnsSubmenu.addAction(columnNames[col]);
		ac->setCheckable(true);
		ac->setChecked( !isColumnHidden(col) );
		connect( ac, &QAction::triggered, [this, col] (bool visible) { setColumnHidden(col, !visible); } );
	}
	rootMenu.addMenu( &columnsSubmenu );

	if( selectedList.count() && (gGlobalConfig.userLevel() > ROSAPIUser::Level::Instalator) )
	{
		QString userName = selectedList.first()->pppSecretMap.first().userName();
		ac = rootMenu.addAction( tr("Borrar usuario %1").arg(userName) );

		connect( ac, &QAction::triggered, [this, userName] () { this->deleteUser(userName); } );

		connect( rootMenu.addAction( tr("Exportar datos de %1 usuario%2").arg(selectedList.count()).arg( (selectedList.count()>1) ? "s" : "") ),
									 &QAction::triggered, [this] () { exportUsersData(); }	);

		chngProfileSubmenu.setTitle( tr("Cambiar perfil a %1 cliente%2").arg(selectedList.count()).arg( (selectedList.count()>1) ? "s" : "") );

		for( QString profileName : gGlobalConfig.clientProfileMap().regularProfileNames() )
		{
			ac = chngProfileSubmenu.addAction( profileName );
			connect( ac, &QAction::triggered, [this, selectedList, profileName] () { this->changeMultipleProfiles(selectedList, profileName); } );
		}
		rootMenu.addMenu( &chngProfileSubmenu );
	}
	rootMenu.exec( event->globalPos() );
}
