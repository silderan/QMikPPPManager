#include "QROSSecretTableWidget.h"

#include <QFont>
#include <QHeaderView>

#include "../ConfigData/QConfigData.h"

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
}

QString QROSSecretTableWidget::createObjectIDKey(const QString &routerName, const QString &rosObjectID)
{
	return QString("%1:%2").arg(routerName, rosObjectID);
}

QROSUserNameWidgetItem *QROSSecretTableWidget::addNewRow(const QString &userName)
{
	int row = rowCount();

	insertRow(row);
	// All right, there is no item. Let's create a new one.
	QROSUserNameWidgetItem *userNameItem = new QROSUserNameWidgetItem();
	// Put it on user name column.
	setItem(row, Columns::UserName, userNameItem);
	userNameItem->setText( userName );

	m_userNameMap[userName] = userNameItem;
	return userNameItem;
}

void QROSSecretTableWidget::setupCellItem(int row, Columns col, const QString &cellText)
{
	if( item(row, col) == Q_NULLPTR )
		setItem(row, static_cast<int>(col), new QTableWidgetItem(cellText));
	else
		item(row, col)->setText(cellText);
}

void QROSSecretTableWidget::onROSSecretModReply(const ROSPPPSecret &rosSecretData)
{
	if( rosSecretData.profile().isEmpty() || gGlobalConfig.clientProfileList().isInternalProfile(rosSecretData.profile()) )
		return;

	QString secretIDKey = createObjectIDKey(rosSecretData.userName(), rosSecretData.rosObjectID());
	QROSUserNameWidgetItem *userNameItem = m_secretIDMap.value(secretIDKey, Q_NULLPTR);

	blockSignals(true);

	if( userNameItem == Q_NULLPTR )
	{
		// If there is no item, maybe there is with de same user-name.
		userNameItem = m_userNameMap.value(rosSecretData.userName(), Q_NULLPTR);

		if( userNameItem == Q_NULLPTR )
			userNameItem = addNewRow(rosSecretData.userName());

		// Copy usefull data.
		userNameItem->staticIP = rosSecretData.staticIP();
		m_secretIDMap[secretIDKey] = userNameItem;
	}

	if( userNameItem->rosPPPSecretIDMap.isEmpty() ||	// It's empty the first time that a secret data comes.
		!userNameItem->rosPPPSecretIDMap[rosSecretData.routerName()].isEmpty() ) // It's not empty when data from this router has been updated.
	{
		// As username is used for key map, has sepecial code.
		if( item(userNameItem->row(), Columns::UserName)->text() != rosSecretData.userName() )
		{
			// Copy the item to the new name key.
			m_userNameMap[rosSecretData.userName()] = m_userNameMap[item(userNameItem->row(), Columns::UserName)->text()];
			m_userNameMap.remove(item(userNameItem->row(), Columns::UserName)->text());
			setupCellItem(userNameItem->row(), UserName,			rosSecretData.userName() );
		}
		setupCellItem( userNameItem->row(), Columns::ClientCode,		rosSecretData.clientCode() );
		setupCellItem( userNameItem->row(), Columns::UserProfile,		rosSecretData.originalProfile() );
		setupCellItem( userNameItem->row(), Columns::ClientName,		rosSecretData.clientName() );
		setupCellItem( userNameItem->row(), Columns::ClientAddress,		rosSecretData.address() );
		setupCellItem( userNameItem->row(), Columns::ClientCity,		rosSecretData.city() );
		setupCellItem( userNameItem->row(), Columns::ClientPhone,		rosSecretData.phones() );
		setupCellItem( userNameItem->row(), Columns::ClientInstaller,	rosSecretData.installerName() );
		setupCellItem( userNameItem->row(), Columns::ClientEmail,		rosSecretData.email() );
		setupCellItem( userNameItem->row(), Columns::ClientAnnotations,	rosSecretData.notes() );

		// This columns can be filled by active data before the
		if( isEmptyCellText(userNameItem->row(), Columns::ActiveUserStatus) )
			setupCellItem( userNameItem->row(), Columns::ActiveUserStatus, tr("Desconectado: %1").arg(rosSecretData.lastLogOff().toString("dd/MM/yyyy HH:mm:ss")) );

		if( isEmptyCellText(userNameItem->row(), Columns::ActiveRouter) )
			setupCellItem( userNameItem->row(), Columns::ActiveRouter,	tr("Ninguno") );

		if( isEmptyCellText(userNameItem->row(), Columns::RemoteIP) )
			setupCellItem( userNameItem->row(), Columns::RemoteIP, userNameItem->staticIP.isValid() ? tr("s:%1").arg(userNameItem->staticIP.toString()) : "" );

		// TODO: Apply special service-status style.
		if( rosSecretData.serviceState().isEmpty() )
		{
			setupCellItem( userNameItem->row(), ClientPaymentStatus, tr("Alta") );
			setupCellItemStyle( userNameItem->row(), ClientPaymentStatus, gGlobalConfig.tableCellLook().m_enabled );
		}
		else
		{
			setupCellItem( userNameItem->row(), ClientPaymentStatus, rosSecretData.serviceState() );
			setupCellItemStyle( userNameItem->row(), ClientPaymentStatus, gGlobalConfig.tableCellLook().m_disabledNoPay );
		}
	}
	userNameItem->rosPPPSecretIDMap[rosSecretData.routerName()] = rosSecretData.rosObjectID();

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
			m_activeIDMap.remove( userNameItem->rosPPPActiveObjectID );
			blockSignals(true);
			removeRow(userNameItem->row());
			blockSignals(false);
		}
	}
}

void QROSSecretTableWidget::onROSActiveModReply(const ROSPPPActive &rosSecretActive)
{
	QROSUserNameWidgetItem *userNameItem = m_userNameMap.value( rosSecretActive.userName(), Q_NULLPTR );

	blockSignals(true);
	// If there is nothing here, could be a active event before the secred has come.
	if( userNameItem == Q_NULLPTR )
		userNameItem = addNewRow(rosSecretActive.userName());

	// That could happen when a new connection comes before a desconnection.
	if( !userNameItem->rosPPPActiveObjectID.isEmpty() )
		m_activeIDMap.remove(userNameItem->rosPPPActiveObjectID);
	userNameItem->rosPPPActiveObjectID = rosSecretActive.rosObjectID();

	m_activeIDMap[rosSecretActive.rosObjectID()] = userNameItem;

	setupCellItem( userNameItem->row(), Columns::ActiveUserStatus, tr("Conectado: %1").arg(rosSecretActive.uptime().toString("dd/MM/yyyy HH:mm:ss")) );
	setupCellItem( userNameItem->row(), Columns::ActiveRouter, rosSecretActive.routerName() );
	setupCellItem( userNameItem->row(), Columns::RemoteIP, rosSecretActive.currentIPv4().toString() );
	blockSignals(false);
}

void QROSSecretTableWidget::onROSActiveDelReply(const QString &routerName, const QString &rosObjectID)
{
	QROSUserNameWidgetItem *userNameItem = m_activeIDMap.value(rosObjectID, Q_NULLPTR);

	// Not found: not yet in table.
	if( userNameItem != Q_NULLPTR )
	{
		// Take care. can be a connection from another router.
		if( item(userNameItem->row(), Columns::ActiveRouter)->text() == routerName )
		{
			blockSignals(true);
			setupCellItem( userNameItem->row(), Columns::ActiveUserStatus, tr("Desconectado: %1").arg(QDateTime::currentDateTime().toString()) );
			setupCellItem( userNameItem->row(), Columns::ActiveRouter, tr("Ninguno") );
			setupCellItem( userNameItem->row(), Columns::RemoteIP, userNameItem->staticIP.isValid() ? tr("s:%1").arg(userNameItem->staticIP.toString()) : "" );
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
	if( (dataTypeID == DataTypeID::PPPSecret) || (dataTypeID == DataTypeID::PPPActive) )
		resizeColumnsToContents();
}

void QROSSecretTableWidget::updateConfig()
{
	QFont tableFont = font();
	tableFont.setPixelSize( gGlobalConfig.tableCellLook().m_fontSize );
	setFont( tableFont );
	verticalHeader()->setDefaultSectionSize( gGlobalConfig.tableCellLook().m_rowHeight );
}

void QROSActiveStatusCellItem::updateStyle()
{

}
