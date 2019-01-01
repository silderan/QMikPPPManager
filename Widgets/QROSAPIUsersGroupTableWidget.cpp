#include "QROSAPIUsersGroupTableWidget.h"

#include "QRoutersLineEdit.h"

QROSAPIUsersGroupTableWidget::QROSAPIUsersGroupTableWidget(QWidget *parent) : QTableWidgetBase(parent)
{
	setColumnCount(TotalColumns);
	setHorizontalHeaderLabels( QStringList() << "Nombre" << "Permisos" << "Routers" );
}

QROSAPIUsersGroupTableWidget::~QROSAPIUsersGroupTableWidget()
{

}

int QROSAPIUsersGroupTableWidget::addGroup(const ROSAPIUsersGroup &groupData)
{
	int row = rowOf( groupData.groupName(), GroupName );

	if( (row >= rowCount()) || (row < 0) )
		insertRow( row = rowCount() );

	setCellText( row, GroupName, groupData.groupName() );
	setCellText( row, Policy, groupData.policy().join(',') );

	if( cellWidget(row, Routers) == Q_NULLPTR )
		setCellWidget( row, Routers, new QRoutersLineEdit() );
	static_cast<QRoutersLineEdit*>(cellWidget(row, Routers))->addRouterID(groupData.routerName(), groupData.dataID());

	return row;
}

QStringList QROSAPIUsersGroupTableWidget::groupNames() const
{
	QStringList ls;
	for( int row = 0; row < rowCount(); ++row )
		ls.append(item(row, GroupName)->text());
	return ls;
}

void QROSAPIUsersGroupTableWidget::onUserLevelChanged(int index)
{

}
