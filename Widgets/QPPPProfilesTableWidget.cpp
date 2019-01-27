#include "QPPPProfilesTableWidget.h"

#include "../ROSData/ROSPPPProfile.h"
#include "QComboBoxItemDelegate.h"
#include "QSpeedTableWidget.h"

QPPPProfilesTableWidget::QPPPProfilesTableWidget(QWidget *papi) :
	QROSDataTableWidget(papi)
{
	setColumnCount(TotalColumns);
	setRouterIDColumn(RoutersColumn);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Velocidades" << "Direccion Router" << "Pool direcciones cliente" << "Bridge" << "Routers" );

	setFancyItemDelegateForColumn( Columns::BridgeColumn, new QComboBoxItemDelegated( this, tr("Ninguno"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.bridgeNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::LocalAddressColumn, new QComboBoxItemDelegated( this, tr("Ninguna"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::RemoteAddressColumn, new QComboBoxItemDelegated( this, tr("Ninguna"), "", false,
													/*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													/*skip list*/				[] (int)			{ return QStringList(); } ) );

	setItemDelegateForColumn( Columns::RateLimitColumn, new QSpeedTableWidgetItemDelegate() );
}

QPPPProfilesTableWidget::~QPPPProfilesTableWidget()
{

}

void QPPPProfilesTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	QROSDataTableWidget::setupRow(row, rosData);

	const ROSPPPProfile &profileData = static_cast<const ROSPPPProfile &>(rosData);
	setCellText( row, ProfileNameColumn, profileData.profileName(), Qt::ItemIsEditable );
	setCellText( row, RateLimitColumn, profileData.rateLimit().toString(), Qt::ItemIsEditable );
	setCellText( row, LocalAddressColumn, profileData.localAddress(), Qt::ItemIsEditable );
	setCellText( row, RemoteAddressColumn, profileData.remoteAddress(), Qt::ItemIsEditable );
	setCellText( row, BridgeColumn, profileData.bridgeName(), Qt::ItemIsEditable );
}

int QPPPProfilesTableWidget::rowOf(const ROSDataBase &rosData)
{
	return QROSDataTableWidget::rowOf( ProfileNameColumn, static_cast<const ROSPPPProfile &>(rosData).profileName() );
}

ROSDataBase *QPPPProfilesTableWidget::getRosData(int row)
{
	ROSPPPProfile *profileData = new ROSPPPProfile("");
	profileData->setProfileName( cellText(row, ProfileNameColumn) );
	profileData->rateLimit().fromString( cellText(row, RateLimitColumn) );
	profileData->setLocalAddress( cellText(row, LocalAddressColumn) );
	profileData->setRemoteAddress( cellText(row, RemoteAddressColumn) );
	profileData->setBridgeName( cellText(row, BridgeColumn) );
	return profileData;
}

void QPPPProfilesTableWidget::updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue)
{
	Q_UNUSED(row);

	ROSPPPProfile *profileData = static_cast<ROSPPPProfile*>(rosData);
	switch( static_cast<Columns>(changedColumn) )
	{
	case QPPPProfilesTableWidget::ProfileNameColumn:
		profileData->setProfileName(newValue);
		break;
	case QPPPProfilesTableWidget::RateLimitColumn:
		profileData->rateLimit().fromString(newValue);
		break;
	case QPPPProfilesTableWidget::LocalAddressColumn:
		profileData->setLocalAddress(newValue);
		break;
	case QPPPProfilesTableWidget::RemoteAddressColumn:
		profileData->setRemoteAddress(newValue);
		break;
	case QPPPProfilesTableWidget::BridgeColumn:
		profileData->setBridgeName(newValue);
		break;
	case QPPPProfilesTableWidget::RoutersColumn:
		Q_ASSERT(false);
		break;
	case QPPPProfilesTableWidget::TotalColumns:
		Q_ASSERT(false);
		break;
	}
}
