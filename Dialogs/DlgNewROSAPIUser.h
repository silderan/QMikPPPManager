#ifndef DLGNEWROSAPIUSER_H
#define DLGNEWROSAPIUSER_H

#include "DlgDataBase.h"

namespace Ui
{
	class DlgNewROSAPIUser;
}

class DlgNewROSAPIUser : public QNewROSDataDialogBase
{
	Q_OBJECT
	Ui::DlgNewROSAPIUser *ui;

public:
	explicit DlgNewROSAPIUser(QWidget *parent = Q_NULLPTR);
	~DlgNewROSAPIUser();

	virtual void setROSData(ROSDataBase &);
	virtual bool getROSData(ROSDataBase &)const;
};

#endif // DLGNEWROSAPIUSER_H
