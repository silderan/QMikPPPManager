#ifndef DLGNEWROSAPIUSER_H
#define DLGNEWROSAPIUSER_H

#include "QNewROSDataDialogBase.h"
#include "../ROSMultiConnectorManager.h"

namespace Ui
{
	class DlgROSAPIUser;
}

class DlgNewROSAPIUser : public QNewROSDataDialogBase
{
	Ui::DlgROSAPIUser *ui;

public:
	explicit DlgNewROSAPIUser(QWidget *papi);
	~DlgNewROSAPIUser();

	virtual void setROSData(ROSDataBase &);
	virtual bool getROSData(ROSDataBase &)const;
};

#endif // DLGNEWROSAPIUSER_H
