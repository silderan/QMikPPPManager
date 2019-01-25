#ifndef DLGNEWPPPPROFILE_H
#define DLGNEWPPPPROFILE_H

#include <QDialog>

#include "../ROSData/ROSPPPProfile.h"

namespace Ui
{
	class DlgNewPPPProfile;
}

class DlgNewPPPProfile : public QDialog
{
	Q_OBJECT
	Ui::DlgNewPPPProfile *ui;

	void raiseWarning(const QString &error, const QString &field) const;
	void setup(const ROSPPPProfile &rosPPPProfile);

public:
	explicit DlgNewPPPProfile(const ROSPPPProfile &rosPPPProfile, QWidget *papi);
	~DlgNewPPPProfile();

	ROSPPPProfile rosPPPProfile()const;

private slots:
	void on_acceptButton_clicked();

};

#endif // DLGNEWPPPPROFILE_H
