#ifndef DLGROSAPIUSERS_H
#define DLGROSAPIUSERS_H

#include "DlgDataBase.h"
#include "../ROSData/ROSAPIUser.h"
#include "../ROSData/ROSAPIUserGroup.h"

namespace Ui
{
	class DlgROSAPIUsers;
}

class DlgROSAPIUsers : public DlgDataBase
{
	Q_OBJECT
	Ui::DlgROSAPIUsers *ui;

public:
	explicit DlgROSAPIUsers(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent);
	~DlgROSAPIUsers()override;

	void onUserDataReceived(const ROSAPIUser &user);
	void onUsersGroupDataReceived(const ROSAPIUsersGroup &group);

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap routerIDMap);

private slots:
	void on_addUserButton_clicked();

public:
	void clear()override;
	void onROSModReply(const ROSDataBase &rosData) override;
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID) override;
	void onROSDone(const QString &routerName, DataTypeID dataTypeID) override;
};

#endif // DLGROSAPIUSERS_H
