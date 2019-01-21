#include "QROSSecretTableWidget.h"

#include <QFont>
#include <QHeaderView>

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
	case ROSPPPSecret::ActiveUndefined:		return gGlobalConfig.tableCellLook().m_enabled;
	case ROSPPPSecret::ActiveTemporally:	return gGlobalConfig.tableCellLook().m_enabled;
	case ROSPPPSecret::CanceledNoPay:		return gGlobalConfig.tableCellLook().m_disabledNoPay;
	case ROSPPPSecret::CanceledTemporally:	return gGlobalConfig.tableCellLook().m_disabledTemporary;
	case ROSPPPSecret::CanceledTechnically:	return gGlobalConfig.tableCellLook().m_disabledTechnically;
	case ROSPPPSecret::CanceledRetired:		return gGlobalConfig.tableCellLook().m_disabledDevicesRetired;
	case ROSPPPSecret::CanceledUndefined:	return gGlobalConfig.tableCellLook().m_disabledUndefined;
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

QROSSecretTableWidget::QROSSecretTableWidget(QWidget *papi) : QTableWidget(papi)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList()
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
							   << tr("Notas") );
	Q_ASSERT( columnCount() == TotalColumns );

	setItemDelegateForColumn( Columns::UserProfile,
							  new QComboBoxItemDelegated( this, "", false,
									/*add list*/			  [] (int)			{ return gGlobalConfig.clientProfileMap().regularProfileNames();	},
									/*skip list*/			  [] (int)			{ return QStringList(); },
									/*selected data*/		  [this] (int row)	{ return originalProfile(row); } ) );

	setItemDelegateForColumn( Columns::RemoteIP,
							  new QComboBoxItemDelegated( this, tr("IP dinámica"), false,
															  [this](int row)	{ return staticIPs(row); },
															  [this](int)		{ return usedStaticIPs(); },
															  [this](int row)	{ return currentIP(row); } ) );

	setItemDelegateForColumn( Columns::Installer,
							  new QComboBoxItemDelegated( this, gGlobalConfig.userName(), false,
															  [](int)			{ return gGlobalConfig.instaladores(); },
															  [](int)			{ return QStringList(); },
															  [this](int row)	{ return item(row, Columns::Installer)->text(); } ) );

	setItemDelegateForColumn( Columns::ServiceStatus,
							  new QComboBoxItemDelegated( this, "", false,
															  [](int)			{ return ROSPPPSecret::serviceStateNames(); },
															  [](int)			{ return QStringList(); },
															  [this](int row)	{ return item(row, Columns::ServiceStatus)->text(); } ) );

	setSortingEnabled(true);
	horizontalHeader()->setSectionsMovable(true);
//	horizontalHeader()->saveState();
	connect( this, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(onCellDobleClic(QTableWidgetItem *)) );
	connect( this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onCellChanged(QTableWidgetItem*)) );
}

bool QROSSecretTableWidget::shouldBeVisible(const QROSUserNameWidgetItem *userNameItem)
{
	foreach( const ROSPPPSecret &rosPPPSecret, userNameItem->rosPPPSecretMap )
		if( gGlobalConfig.clientProfileMap().containsProfileName(rosPPPSecret.pppProfile()) )
			return true;
	return false;
}

void QROSSecretTableWidget::showRowIfValid(const QROSUserNameWidgetItem *userNameItem)
{
	shouldBeVisible(userNameItem) ? showRow(userNameItem->row()) : hideRow(userNameItem->row());
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

void QROSSecretTableWidget::setupCellItem(int row, Columns col, const QString &cellText)
{
	if( item(row, col) == Q_NULLPTR )
		setItem(row, col, new QTableWidgetItem(cellText));
	else
		item(row, col)->setText(cellText);
}

void QROSSecretTableWidget::setupServiceCellItem(int row, ROSPPPSecret::ServiceState st)
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
	setupRemoteIPCellItem( userNameItem->row(), userNameItem->rosPPPActive.currentIPv4(), userNameItem->rosPPPSecretMap.isEmpty() ? IPv4() : userNameItem->rosPPPSecretMap.first().staticIP() );
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

void QROSSecretTableWidget::onROSSecretModReply(const ROSPPPSecret &rosPPPSecret)
{
	if( rosPPPSecret.pppProfile().isEmpty() )
		return;

	blockSignals(true);

	QROSUserNameWidgetItem *userNameItem;

	// Find the item by the pair routerName-rosObjectID (the ObjectIDKey)...
	if( (userNameItem = m_secretIDMap.value(createObjectIDKey(rosPPPSecret), Q_NULLPTR)) == Q_NULLPTR )
	{
		// ...or by the name if it was created before by the a secretActive event.
		if( (userNameItem = m_userNameMap.value(rosPPPSecret.userName(), Q_NULLPTR)) == Q_NULLPTR )
			userNameItem = addNewRow(rosPPPSecret.userName());

//		userNameItem->rosCachedPPPSecret = rosPPPSecret;
		m_secretIDMap[createObjectIDKey(rosPPPSecret)] = userNameItem;
	}
	userNameItem->rosPPPSecretMap.insert(rosPPPSecret.routerName(), rosPPPSecret);

	// As username is key for this map, has special code.
	if( item(userNameItem->row(), Columns::UserName)->text() != rosPPPSecret.userName() )
	{
		// Copy the item to the new name key.
		m_userNameMap[rosPPPSecret.userName()] = m_userNameMap.take( item(userNameItem->row(), Columns::UserName)->text() );
		setupCellItem(userNameItem->row(), UserName,				rosPPPSecret.userName() );
	}

	userNameItem->rosPPPSecretIDMap[rosPPPSecret.routerName()] = rosPPPSecret.rosObjectID();

	setupCellItem( userNameItem->row(), Columns::ClientCode,		rosPPPSecret.clientCode() );
	setupCellItem( userNameItem->row(), Columns::UserProfile,		rosPPPSecret.originalProfile() );
	setupCellItem( userNameItem->row(), Columns::ClientName,		rosPPPSecret.clientName() );
	setupCellItem( userNameItem->row(), Columns::ClientAddress,		rosPPPSecret.clientAddress() );
	setupCellItem( userNameItem->row(), Columns::ClientCity,		rosPPPSecret.clientCity() );
	setupCellItem( userNameItem->row(), Columns::ClientPhone,		rosPPPSecret.clientPhones() );
	setupCellItem( userNameItem->row(), Columns::Installer,			rosPPPSecret.installerName() );
	setupCellItem( userNameItem->row(), Columns::ClientEmail,		rosPPPSecret.clientEmail() );
	setupCellItem( userNameItem->row(), Columns::ClientAnnotations,	rosPPPSecret.clientNotes() );

	// This columns can be filled by active data before the secred was reported. So, here will set data only if they're empty.
	// TODO: Last logg off must show the last (date-nearest) value because every router will has diferent time-stamp.
	//       Maybe, could be interesting also keep all data and show to user via cell tool-tip
	if( item(userNameItem->row(), Columns::ActiveUserStatus) == Q_NULLPTR )
		setupActiveStatusCellItem( userNameItem->row(), QDateTime(), rosPPPSecret.lastLogOff() );

	if( item(userNameItem->row(), Columns::ActiveRouter) == Q_NULLPTR )
		setupCellItem( userNameItem->row(), Columns::ActiveRouter,	tr("Ninguno") );

	setupRemoteIPCellItem( userNameItem );

	// Quite a long statement... just to pass a CanceledUndefined parameter if client has service canceled but their state does not match.
	setupServiceCellItem( userNameItem->row(),
//						  gGlobalConfig.clientProfileList().isDisabledProfile(rosSecretData.profile()) && (rosSecretData.serviceState() < ROSPPPSecret::ServiceState::CanceledNoPay)
//						  ? ROSPPPSecret::ServiceState::CanceledUndefined :
							rosPPPSecret.serviceState() );

	showRowIfValid( userNameItem );

	blockSignals(false);
}

void QROSSecretTableWidget::onROSSecretDelReply(const QString &routerName, const QString &rosObjectID)
{
	QString key = createObjectIDKey(routerName, rosObjectID);
	QROSUserNameWidgetItem *userNameItem = m_secretIDMap.value(key, Q_NULLPTR);

	if( userNameItem == Q_NULLPTR )
	{
		userNameItem->rosPPPSecretIDMap.remove( routerName );
		if( userNameItem->rosPPPSecretIDMap.isEmpty() )
		{
			m_userNameMap.remove( userNameItem->text() );
			m_secretIDMap.remove( key );
			m_activeIDMap.remove( userNameItem->rosPPPActive.rosObjectID() );
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
	if( !userNameItem->rosPPPActive.rosObjectID().isEmpty() )
		m_activeIDMap.remove(userNameItem->rosPPPActive.rosObjectID());

	userNameItem->rosPPPActive = rosPPPActive;

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
		userNameItem->rosPPPActive = ROSPPPActive("");
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

void QROSSecretTableWidget::onCellDobleClic(QTableWidgetItem *item)
{
	if( item->column() == static_cast<int>(Columns::UserName) )
	{
		QROSUserNameWidgetItem *userNameItem = static_cast<QROSUserNameWidgetItem*>(item);
		emit editPPPUser( userNameItem->rosPPPSecretMap, userNameItem->rosPPPActive );
	}
}

void QROSSecretTableWidget::onCellChanged(QTableWidgetItem *item)
{
	QROSUserNameWidgetItem *userNameItem = userNameWidgetItem(item->row());
	Q_ASSERT(userNameItem);
	if( userNameItem )
	{
		QString newText = item->text();
		switch( static_cast<Columns>(item->column()) )
		{
		case QROSSecretTableWidget::UserName:
			if( userNameItem->rosPPPSecretMap.first().userName() != item->text() )
			{
				blockSignals(true);
				item->setText(userNameItem->rosPPPSecretMap.first().userName());
				blockSignals(false);
			}
			break;
		case QROSSecretTableWidget::ClientCode:
			break;
		case QROSSecretTableWidget::ServiceStatus:
			break;
		case QROSSecretTableWidget::UserProfile:
			if( userNameItem->rosPPPSecretMap.first().originalProfile() != item->text() )
			{
				blockSignals(true);
				item->setText(userNameItem->rosPPPSecretMap.first().originalProfile());
				blockSignals(false);
				ROSPPPSecret newSecret = userNameItem->rosPPPSecretMap.first();
				newSecret.setOriginalProfile(newText);
				if( newSecret.pppProfile() != gGlobalConfig.clientProfileMap().serviceCanceledProfile().profileName() )
					newSecret.setPPPProfile(newText);
				QRouterIDMap routerIDMap;
				foreach( const ROSPPPSecret &secret, userNameItem->rosPPPSecretMap )
					routerIDMap[secret.routerName()] = secret.rosObjectID();

				multiConnectionManager.updateRemoteData(newSecret, routerIDMap);
			}
			break;
		case QROSSecretTableWidget::ActiveUserStatus:
			break;
		case QROSSecretTableWidget::ActiveRouter:
			break;
		case QROSSecretTableWidget::RemoteIP:
			break;
		case QROSSecretTableWidget::ClientName:
			break;
		case QROSSecretTableWidget::ClientAddress:
			break;
		case QROSSecretTableWidget::ClientCity:
			break;
		case QROSSecretTableWidget::ClientPhone:
			break;
		case QROSSecretTableWidget::Installer:
			break;
		case QROSSecretTableWidget::ClientEmail:
			break;
		case QROSSecretTableWidget::ClientAnnotations:
			break;
		case QROSSecretTableWidget::TotalColumns:
			break;
		}
	}
}
