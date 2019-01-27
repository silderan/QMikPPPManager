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
	case ServiceState::CanceledRetired:		return gGlobalConfig.tableCellLook().m_disabledDevicesRetired;
	case ServiceState::CanceledUndefined:	return gGlobalConfig.tableCellLook().m_disabledUndefined;
	}
	Q_ASSERT(false);
	return gGlobalConfig.tableCellLook().m_enabled;
}

void QROSActiveStatusCellItem::updateText()
{
	if( m_uptime.isValid() )
		setText( QString("C: %1").arg(m_uptime.toString("dd/MM/yyyy hh:mm:ss")) );
	else
		setText( QString("D: %1").arg(m_downtime.toString("dd/MM/yyyy hh:mm:ss")) );
}

const CellLook &QROSActiveStatusCellItem::getCellLook()
{
	if( m_uptime.isValid() )
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
				<< tr("Contrato")
				<< tr("Perfil")
				<< tr("Estado")
				<< tr("Router")
				<< tr("IP")
				<< tr("Nombre cliente")
				<< tr("Dirección")
				<< tr("Población")
				<< tr("Teléfonos")
				<< tr("Instalador")
				<< tr("Email")
				<< tr("Notas") ;
		Q_ASSERT( rtn.count() == TotalColumns );
	}
	return rtn;
}

QROSSecretTableWidget::QROSSecretTableWidget(QWidget *papi) : QTableWidget(papi)
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

bool QROSSecretTableWidget::shouldBeVisible(const QROSUserNameWidgetItem *userNameItem)
{
	foreach( const ROSPPPSecret &rosPPPSecret, userNameItem->pppSecretMap )
		if( gGlobalConfig.clientProfileMap().containsProfileName(rosPPPSecret.pppProfileName()) )
			return true;
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

void QROSSecretTableWidget::setupCellItem(int row, Columns col, const QString &cellText)
{
	if( item(row, col) == Q_NULLPTR )
		setItem(row, col, new QTableWidgetItem(cellText));
	else
		item(row, col)->setText(cellText);
}

void QROSSecretTableWidget::setupServiceCellItem(int row, ServiceState::Type st)
{
	if( item(row, Columns::ServiceStatus) == Q_NULLPTR )
		setItem(row, Columns::ServiceStatus, new QROSServiceStatusCellItem());
	static_cast<QROSServiceStatusCellItem*>(item(row, Columns::ServiceStatus))->setServiceState(st);
}

void QROSSecretTableWidget::setupActiveStatusCellItem(int row, const QDateTime &uptime, const QDateTime &downtime)
{
	if( item(row, Columns::ActiveUserStatus) == Q_NULLPTR )
		setItem(row, Columns::ActiveUserStatus, new QROSActiveStatusCellItem());

	static_cast<QROSActiveStatusCellItem*>(item(row, Columns::ActiveUserStatus))->setTimes(uptime, downtime);
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
		setupCellItem(userNameItem->row(), UserName,				pppSecret.userName() );
	}

	setupCellItem( userNameItem->row(), Columns::ClientCode,		pppSecret.clientCode() );
	setupCellItem( userNameItem->row(), Columns::UserProfile,		pppSecret.originalProfile() );
	setupCellItem( userNameItem->row(), Columns::ClientName,		pppSecret.clientName() );
	setupCellItem( userNameItem->row(), Columns::ClientAddress,		pppSecret.clientAddress() );
	setupCellItem( userNameItem->row(), Columns::ClientCity,		pppSecret.clientCity() );
	setupCellItem( userNameItem->row(), Columns::ClientPhone,		pppSecret.clientPhones() );
	setupCellItem( userNameItem->row(), Columns::Installer,			pppSecret.installerName() );
	setupCellItem( userNameItem->row(), Columns::ClientEmail,		pppSecret.clientEmail() );
	setupCellItem( userNameItem->row(), Columns::ClientAnnotations,	pppSecret.clientNotes() );

	// This columns can be filled by active data before the secred was reported. So, here will set data only if they're empty.
	// TODO: Last logg off must show the last (date-nearest) value because every router will has diferent time-stamp.
	//       Maybe, could be interesting also keep all data and show to user via cell tool-tip
	if( item(userNameItem->row(), Columns::ActiveUserStatus) == Q_NULLPTR )
		setupActiveStatusCellItem( userNameItem->row(), QDateTime(), pppSecret.lastLogOff() );

	if( item(userNameItem->row(), Columns::ActiveRouter) == Q_NULLPTR )
		setupCellItem( userNameItem->row(), Columns::ActiveRouter,	tr("Ninguno") );

	setupRemoteIPCellItem( userNameItem );

	// Quite a long statement... just to pass a CanceledUndefined parameter if client has service canceled but their state does not match.
	setupServiceCellItem( userNameItem->row(),
//						  gGlobalConfig.clientProfileList().isDisabledProfile(rosSecretData.profile()) && (rosSecretData.serviceState() < ROSPPPSecret::ServiceState::CanceledNoPay)
//						  ? ROSPPPSecret::ServiceState::CanceledUndefined :
							pppSecret.serviceState() );

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

	setupActiveStatusCellItem( userNameItem->row(), rosPPPActive.uptime(), QDateTime() );
	setupRemoteIPCellItem( userNameItem );
	setupCellItem( userNameItem->row(), Columns::ActiveRouter, rosPPPActive.routerName() );
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
			setupActiveStatusCellItem( userNameItem->row(), QDateTime(), QDateTime::currentDateTime() );
			setupCellItem( userNameItem->row(), Columns::ActiveRouter, tr("Ninguno") );
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

void QROSSecretTableWidget::updateConfig()
{
	QFont tableFont = font();
	tableFont.setPixelSize( gGlobalConfig.tableCellLook().m_fontSize );
	setFont( tableFont );
	verticalHeader()->setDefaultSectionSize( gGlobalConfig.tableCellLook().m_rowHeight );
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
	QROSUserNameWidgetItem *userNameItem = userNameWidgetItem(index.row());
	Q_ASSERT(userNameItem);
	ROSPPPSecret newSecret = userNameItem->pppSecretMap.first();

	std::function<bool(ROSPPPSecret &, const QString &)> setFnc;
	QString fieldName;

	if( userNameItem )
	{
		switch( static_cast<Columns>(index.column()) )
		{
		case QROSSecretTableWidget::UserName:
			Q_ASSERT(false);
			break;
		case QROSSecretTableWidget::ClientCode:
			fieldName = tr("Código de cliente");
			setFnc = &ROSPPPSecret::setClientCode;
			break;
		case QROSSecretTableWidget::ServiceStatus:
			// This is not a string, so cannot be set by setFnc
			newSecret.setServiceState( ServiceState::fromNameString(newText) );
			if( ServiceState::isActiveState(newSecret.serviceState()) && (newSecret.pppProfileName() == gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName()) )
				newSecret.setPPPProfileName(newSecret.originalProfile());
			else
			if( !ServiceState::isActiveState(newSecret.serviceState()) && (newSecret.pppProfileName() != gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName()) )
				newSecret.setPPPProfileName(gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName());
			multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
			break;
		case QROSSecretTableWidget::UserProfile:
			// This is a special case where two fields changes at once.
			newSecret.setOriginalProfile(newText);
			if( newSecret.pppProfileName() != gGlobalConfig.clientProfileMap().serviceCanceledProfile().pppProfileName() )
				newSecret.setPPPProfileName(newText);
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
		case QROSSecretTableWidget::TotalColumns:
			Q_ASSERT(false);
			break;
		}
	}

	if( !fieldName.isEmpty() && checkStringData( newSecret, fieldName, newText, setFnc) )
		multiConnectionManager.updateRemoteData(newSecret, userNameItem->pppSecretMap.toRouterIDMap());
	return false;
}

void QROSSecretTableWidget::disconnectSelected()
{
	foreach( const QModelIndex &index, selectedIndexes() )
	{
		ROSPPPActive &rosActive = userNameWidgetItem(index.row())->pppActive;
		if( !rosActive.rosObjectID().isEmpty() && !rosActive.deleting() )
		{
			rosActive.setDeleting(true);
			multiConnectionManager.updateRemoteData(rosActive);
		}
	}
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
	QList<QROSUserNameWidgetItem*> selectedList = selectedUsers();
	QList<QROSUserNameWidgetItem*> connectedList;
	foreach( QROSUserNameWidgetItem *userNameItem, selectedList )
	{
		if( userNameItem->pppActive.currentIPv4().isValid() && !connectedList.contains(userNameItem) )
			connectedList.append( userNameItem );
	}

	QMenu menu(this);
	if( !connectedList.isEmpty() )
	{
		QString txt;
		if( connectedList.count() == 1 )
			txt = tr("Desconectar cliente %1").arg(connectedList.first()->pppActive.userName());
		else
			txt = tr("Desconectar %1 clientes").arg(connectedList.count());
		connect( menu.addAction(txt), &QAction::triggered, this, &QROSSecretTableWidget::disconnectSelected );
	}

	QMenu openBrowser( tr("Abrir navegador") );
	foreach( const QROSUserNameWidgetItem *userNameItem, connectedList )
	{
		const ROSPPPActive &rosActive = userNameItem->pppActive;
		if( rosActive.currentIPv4().isValid() )
		{
			openBrowser.setTitle( tr("Abrir http://%1:...").arg(rosActive.currentIPv4().toString()) );
			QMapIterator<QString, quint16> it(gGlobalConfig.openPortsMap());
			while( it.hasNext() )
			{
				it.next();
				QString url = QString("http://%1:%2").arg(rosActive.currentIPv4().toString()).arg(it.value());
				QAction *ac = openBrowser.addAction( QString("puerto %1 (%2)").arg(it.value()).arg(it.key()) );
				connect( ac, &QAction::triggered, [url] () { QDesktopServices::openUrl( QUrl(url) ); } );
			}
			menu.addMenu( &openBrowser );
			break;
		}
	}

	QMenu columns( tr("Columnas") );
	QStringList columnNames = columnsNames();
	for( int col = 0; col < columnNames.count(); ++col )
	{
		QAction *ac = columns.addAction(columnNames[col]);
		ac->setCheckable(true);
		ac->setChecked( !isColumnHidden(col) );
		connect( ac, &QAction::triggered, [this, col] (bool visible) { setColumnHidden(col, !visible); } );
	}
	menu.addMenu( &columns );

	QMenu deleteUser( tr("Borra usuario") );
	if( selectedList.count() )
	{
		QString userName = selectedList.first()->pppSecretMap.first().userName();
		QAction *ac = menu.addAction( tr("Borrar usuario %1").arg(userName) );

		connect( ac, &QAction::triggered, [this, userName] () { this->deleteUser(userName); } );
	}
	int count = selectedList.count() ? selectedList.count() : rowCount();
	if( rowCount() )
	{
		menu.addSeparator();
		connect( menu.addAction( tr("Esportar datos de %1 usuario%2").arg(count).arg( (count>1) ? "s" : "") ), &QAction::triggered,
				 [this] () { exportUsersData(); }	);
	}
	menu.exec( event->globalPos() );
}
