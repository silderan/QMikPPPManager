#include "QROSAPIUserTableWidget.h"
#include "QROSAPIUserLevelComboBox.h"
#include "QROSAPIUsersGroupComboBox.h"

QROSAPIUserTableWidget::QROSAPIUserTableWidget(QWidget *papi) : QTableWidgetBase(papi)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Usuario" << "Grupo" << "Nivel/Tipo" << "Routers" );
	setItemDelegateForColumn(GroupName, new QROSAPIUsersGroupComboBoxDelegate());
	setItemDelegateForColumn(UserLevel, new QROSAPIUserLevelComboBoxDelegate());
	connect( this, SIGNAL(cellChanged(int,int)), this, SLOT(onCellChanged(int,int)) );
}

QROSAPIUserTableWidget::~QROSAPIUserTableWidget()
{

}

int QROSAPIUserTableWidget::rowByName(const QString &groupName)const
{
	for( int row = 0; row < rowCount(); ++row )
	{
		if( item(row, UserName)->text() == groupName )
			return row;
	}
	return -1;
}

int QROSAPIUserTableWidget::addUser(const ROSAPIUser &userData)
{
	blockSignals(true);
	int row = rowOf( userData.userName(), UserName );

	if( (row >= rowCount()) || (row < 0) )
		insertRow( row = rowCount() );

	setCellText( row, UserName, userData.userName() );
	setCellText( row, GroupName, userData.groupName() );
	setCellText( row, UserLevel, userData.levelName() );
	addCellRoutersID( row, Routers, userData.routerName(), userData.dataID() );
	blockSignals(false);
	return row;
}

void QROSAPIUserTableWidget::removeUser(const ROSAPIUser &userData)
{
	int row = rowByName( userData.userName() );
	if( row != -1 )
	{
		delCellRoutersID(row, Routers, userData.routerName());
		if( routersCount(row, Routers) == 0 )
			removeRow(row);
	}
}

void QROSAPIUserTableWidget::onCellChanged(int row, int col)
{
	if( (col == UserLevel) || (col == GroupName) )
	{
		ROSAPIUser rosAPIUserData( "" );
		rosAPIUserData.setUserName( userName(row) );
		rosAPIUserData.setUserLevel( userLevel(row) );
		rosAPIUserData.setGroupName( userGroup(row) );
		emit userModified( rosAPIUserData, routerIDMap(row, Routers) );
	}
}
