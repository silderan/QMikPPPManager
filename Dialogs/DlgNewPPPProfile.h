#ifndef DLGNEWPPPPROFILE_H
#define DLGNEWPPPPROFILE_H

#include "DlgDataBase.h"
#include "../ROSData/ROSPPPProfile.h"

namespace Ui
{
	class DlgNewPPPProfile;
}

class DlgNewPPPProfile : public QNewROSDataDialogBase
{
	Ui::DlgNewPPPProfile *ui;

	void setup(const ROSPPPProfile &rosPPPProfile);

public:
	explicit DlgNewPPPProfile(QWidget *papi);
	~DlgNewPPPProfile();

	virtual void setROSData(ROSDataBase &rosData) Q_DECL_OVERRIDE;
	virtual bool getROSData(ROSDataBase &rosData) const Q_DECL_OVERRIDE;
};

#endif // DLGNEWPPPPROFILE_H
