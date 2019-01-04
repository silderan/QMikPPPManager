#ifndef DLGROSAPIUSER_H
#define DLGROSAPIUSER_H

#include <QDialog>

#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgROSAPIUser;
}

class DlgROSAPIUser : public QDialog
{
	Q_OBJECT

	Ui::DlgROSAPIUser *ui;

private slots:
	void onTextChanged(QString txt);
	void on_acceptButton_clicked();

public:
	explicit DlgROSAPIUser(QWidget *papi = Q_NULLPTR);
	~DlgROSAPIUser();

	ROSAPIUser rosAPIUser();

public:
	static ROSAPIUser getRosAPIUser(QWidget *papi);
};

#endif // DLGROSAPIUSER_H
