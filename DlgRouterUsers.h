#ifndef DLGROUTERUSERS_H
#define DLGROUTERUSERS_H

#include <QDialog>

namespace Ui
{
	class DlgRouterUsers;
}

class DlgRouterUsers : public QDialog
{
	Q_OBJECT

	Ui::DlgRouterUsers *ui;

public:
	explicit DlgRouterUsers(QWidget *parent = Q_NULLPTR);
	~DlgRouterUsers();

private slots:
	void on_acceptButton_clicked();
	void on_addUserButton_clicked();
	void on_delUserButton_clicked();
};

#endif // DLGROUTERUSERS_H
