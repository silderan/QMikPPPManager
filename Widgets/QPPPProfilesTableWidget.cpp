#include "QPPPProfilesTableWidget.h"

#include "../ROSData/ROSPPPProfile.h"
#include "QComboBoxItemDelegate.h"
#include "QSpeedTableWidget.h"

QPPPProfilesTableWidget::QPPPProfilesTableWidget(QWidget *papi) :
	QTableWidgetBase(papi)
{
	setColumnCount(TotalColumns);
	setRouterIDColumn(RoutersColumn);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Velocidades" << "Direccion Router" << "Pool direcciones cliente" << "Bridge" << "Routers" );

	setItemDelegateForColumn( Columns::BridgeColumn, new QComboBoxItemDelegated( this, "", false,
													 /*add list*/				[] (int)			{ return multiConnectionManager.bridgeNameList();	},
													 /*skip list*/				[] (int)			{ return QStringList(); },
													 /*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

	setItemDelegateForColumn( Columns::LocalAddressColumn, new QComboBoxItemDelegated( this, "", false,
													 /*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													 /*skip list*/				[] (int)			{ return QStringList(); },
													 /*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

	setItemDelegateForColumn( Columns::RemoteAddressColumn, new QComboBoxItemDelegated( this, "", false,
													 /*add list*/				[] (int)			{ return multiConnectionManager.poolNameList();	},
													 /*skip list*/				[] (int)			{ return QStringList(); },
													 /*allow change*/			[] (const QModelIndex &,const QString &)	{ return true; } ) );

	setItemDelegateForColumn( Columns::RateLimitColumn, new QSpeedTableWidgetItemDelegate() );
}

QPPPProfilesTableWidget::~QPPPProfilesTableWidget()
{

}

void QPPPProfilesTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	QTableWidgetBase::setupRow(row, rosData);

	const ROSPPPProfile &profileData = static_cast<const ROSPPPProfile &>(rosData);
	setCellText( row, ProfileNameColumn, profileData.profileName(), Qt::ItemIsEditable );
	setCellText( row, RateLimitColumn, profileData.rateLimit().toString(), Qt::ItemIsEditable );
	setCellText( row, LocalAddressColumn, profileData.localAddress(), Qt::ItemIsEditable );
	setCellText( row, RemoteAddressColumn, profileData.remoteAddress(), Qt::ItemIsEditable );
	setCellText( row, BridgeColumn, profileData.bridgeName(), Qt::ItemIsEditable );
}

int QPPPProfilesTableWidget::rowOf(const ROSDataBase &rosData)
{
	return QTableWidgetBase::rowOf( ProfileNameColumn, static_cast<const ROSPPPProfile &>(rosData).profileName() );
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
