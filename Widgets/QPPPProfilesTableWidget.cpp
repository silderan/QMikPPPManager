#include "QPPPProfilesTableWidget.h"

#include "../ROSData/ROSPPPProfile.h"

QPPPProfilesTableWidget::QPPPProfilesTableWidget(QWidget *papi) :
	QTableWidgetBase(papi)
{
	setColumnCount(TotalColumns);
	setRouterIDColumn(RoutersColumn);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Velocidades" << "Direccion Router" << "Pool direcciones cliente" << "Bridge" << "Routers" );
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
