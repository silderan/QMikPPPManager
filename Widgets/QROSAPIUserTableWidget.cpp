#include "QROSAPIUserTableWidget.h"
#include "../ROSMultiConnectorManager.h"

QROSAPIUserTableWidget::QROSAPIUserTableWidget(QWidget *papi) : QROSDataTableWidget(papi)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Usuario" << "Grupo" << "Nivel/Tipo" << "Routers" );
	setRouterIDColumn(Routers);

	setFancyItemDelegateForColumn( Columns::GroupName, new QComboBoxItemDelegated( this, "", "", false,
													/*add list*/				[] (int) { return multiConnectionManager.rosAPIUsersGrupList();	},
													/*skip list*/				[] (int) { return QStringList(); } ) );

	setFancyItemDelegateForColumn( Columns::UserLevel, new QComboBoxItemDelegated( this, "", "", false,
													/*add list*/				[] (int) { return ROSAPIUser::levelNames();	},
													/*skip list*/				[] (int) { return QStringList(); } ) );
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

	QROSDataTableWidget::setupRow(row, rosData);
	setCellText( row, UserName, userData.userName(), userData.rosObjectID().isEmpty() ? Qt::ItemIsEditable : Qt::NoItemFlags );
	setCellText( row, GroupName, userData.groupName(), Qt::ItemIsEditable );
	setCellText( row, UserLevel, userData.levelName(), Qt::ItemIsEditable );
}


int QROSAPIUserTableWidget::rowOf(const ROSDataBase &rosData)
{
	const ROSAPIUser &userData = static_cast<const ROSAPIUser&>(rosData);
	return QROSDataTableWidget::rowOf(UserName, userData.userName());
}

void QROSAPIUserTableWidget::updateROSData(ROSDataBase *rosData, int row, int changedColumn, const QString &newValue)
{
	Q_UNUSED(row);

	ROSAPIUser *apiUser = static_cast<ROSAPIUser*>(rosData);
	switch( static_cast<Columns>(changedColumn) )
	{
	case QROSAPIUserTableWidget::UserName:
		// API User Name is not allowed by ROS.
		Q_ASSERT(false);
		break;
	case QROSAPIUserTableWidget::GroupName:
		apiUser->setGroupName(newValue);
		break;
	case QROSAPIUserTableWidget::UserLevel:
		apiUser->setUserLevel(newValue);
		break;
	case QROSAPIUserTableWidget::Routers:
		Q_ASSERT(false);
		break;
	case QROSAPIUserTableWidget::TotalColumns:
		Q_ASSERT(false);
		break;
	}
}
