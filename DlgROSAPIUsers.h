#ifndef DLGROSAPIUSERS_H
#define DLGROSAPIUSERS_H

#include <QDialog>

#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgROSAPIUsers;
}

class DlgROSAPIUsers : public QDialog
{
	Q_OBJECT
	Ui::DlgROSAPIUsers *ui;

public:
	explicit DlgROSAPIUsers(QWidget *parent = 0);
	~DlgROSAPIUsers();

	void onUserDataReceived(const ROSAPIUser &user);
	void onUsersGroupDataReceived(const ROSAPIUsersGroup &group);

signals:
	void userModified(const ROSAPIUser &rosAPIUser, const QRouterIDMap routerIDMap);
};

#endif // DLGROSAPIUSERS_H
