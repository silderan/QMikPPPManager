#include "QROSAPIUserTableWidget.h"
#include "QROSAPIUserLevelComboBox.h"
#include "QROSAPIUsersGroupComboBox.h"
#include "../ROSMultiConnectorManager.h"

QROSAPIUserTableWidget::QROSAPIUserTableWidget(QWidget *papi) : QTableWidgetBase(papi)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Usuario" << "Grupo" << "Nivel/Tipo" << "Routers" );
	setRouterIDColumn(Routers);
	setItemDelegateForColumn(GroupName, new QROSAPIUsersGroupComboBoxDelegate());
	setItemDelegateForColumn(UserLevel, new QROSAPIUserLevelComboBoxDelegate());
}

QROSAPIUserTableWidget::~QROSAPIUserTableWidget()
{

}

ROSDataBase *QROSAPIUserTableWidget::getRosData(int row)
{
	ROSAPIUser *rosAPIUserData = new ROSAPIUser("");
	rosAPIUserData->setUserName( userName(row) );
	rosAPIUserData->setUserLevel( userLevel(row) );
	rosAPIUserData->setGroupName( userGroup(row) );
	return rosAPIUserData;
}

void QROSAPIUserTableWidget::setupRow(int row, const ROSDataBase &rosData)
{
	const ROSAPIUser &userData = static_cast<const ROSAPIUser&>(rosData);

	Q_ASSERT( !userData.userName().isEmpty() );

	QTableWidgetBase::setupRow(row, rosData);
	setCellText( row, UserName, userData.userName(), userData.rosObjectID().isEmpty() ? Qt::ItemIsEditable : Qt::NoItemFlags );
	setCellText( row, GroupName, userData.groupName(), Qt::ItemIsEditable );
	setCellText( row, UserLevel, userData.levelName(), Qt::ItemIsEditable );
}


int QROSAPIUserTableWidget::rowOf(const ROSDataBase &rosData)
{
	const ROSAPIUser &userData = static_cast<const ROSAPIUser&>(rosData);
	return QTableWidgetBase::rowOf(UserName, userData.userName());
}
