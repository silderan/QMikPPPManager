#ifndef DLGPPPPROFILES_H
#define DLGPPPPROFILES_H

#include <QDialog>

#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgPPPProfiles;
}

class DlgPPPProfiles : public QDialog
{
	Q_OBJECT

	Ui::DlgPPPProfiles *ui;

	ROSMultiConnectManager *m_mktAPI;

public:
	explicit DlgPPPProfiles(ROSMultiConnectManager *mktAPI, QWidget *parent);
	~DlgPPPProfiles();

private slots:
	void on_acceptButton_clicked();

public slots:
	void clear();
};

#endif // DLGPPPPROFILES_H
