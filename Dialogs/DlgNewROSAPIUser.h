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
	void updateGUI();

public:
	explicit DlgNewROSAPIUser(QWidget *parent = Q_NULLPTR);
	~DlgNewROSAPIUser() Q_DECL_OVERRIDE;

	virtual void setROSData(ROSDataBase &) Q_DECL_OVERRIDE;
	virtual bool getROSData(ROSDataBase &)const Q_DECL_OVERRIDE;

	void onConfigChanged() Q_DECL_OVERRIDE;
};

#endif // DLGNEWROSAPIUSER_H
