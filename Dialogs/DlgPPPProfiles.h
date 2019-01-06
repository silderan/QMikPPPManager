#ifndef DLGPPPPROFILES_H
#define DLGPPPPROFILES_H

#include <QDialog>
#include "../ROSData/ROSPPPProfile.h"

namespace Ui
{
	class DlgPPPProfiles;
}

class DlgPPPProfiles : public QDialog
{
	Q_OBJECT

	Ui::DlgPPPProfiles *ui;

public:
	explicit DlgPPPProfiles(QWidget *parent);
	~DlgPPPProfiles();

private slots:
	void on_acceptButton_clicked();

public slots:
	void clear();
	void onPPPProfileDataReceived(const ROSPPPProfile &profileData);

signals:
	void dataModified(const ROSDataBase &rosData, const QRouterIDMap &routerIDMap);
};

#endif // DLGPPPPROFILES_H
