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
	explicit DlgROSAPIUsers(QWidget *parent = Q_NULLPTR);
	~DlgROSAPIUsers();

	void onUserDataReceived(const ROSAPIUser &user);
	void onUsersGroupDataReceived(const ROSAPIUsersGroup &group);

signals:
	void userModified(const ROSDataBase &rosAPIUser, const QRouterIDMap routerIDMap);
	void groupModified(const ROSDataBase &rosAPIUsersGroup, const QRouterIDMap routerIDMap);

public slots:
	void clear();

private slots:
	void on_addUserButton_clicked();
};

#endif // DLGROSAPIUSERS_H
