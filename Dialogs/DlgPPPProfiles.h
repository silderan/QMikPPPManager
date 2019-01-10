#ifndef DLGPPPPROFILES_H
#define DLGPPPPROFILES_H

#include "DlgDataBase.h"
#include "../ROSData/ROSPPPProfile.h"

namespace Ui
{
	class DlgPPPProfiles;
}

class DlgPPPProfiles : public DlgDataBase
{
	Q_OBJECT

	Ui::DlgPPPProfiles *ui;

public:
	explicit DlgPPPProfiles(QWidget *parent, ROSMultiConnectManager &rosMultiConnectManager);
	~DlgPPPProfiles()override;

private slots:
	void on_acceptButton_clicked();

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);

public:
	void clear()override;
	void onROSModReply(const ROSDataBase &rosData) override;
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID) override;
	void onROSDone(const QString &routerName, DataTypeID dataTypeID) override;
};

#endif // DLGPPPPROFILES_H
