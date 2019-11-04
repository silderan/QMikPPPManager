#ifndef DLGPORTEDIT_H
#define DLGPORTEDIT_H

#include <QDialog>

#include "Utils/PortForward.h"
namespace Ui
{
	class DlgPortEdit;
}


class DlgPortEdit : public QDialog
{
	Q_OBJECT
	Ui::DlgPortEdit *ui;
	PortForward mValidPort;

	void onAcceptButtonClicked();
public:
	DlgPortEdit(const PortForward &port, QWidget *parent);
	~DlgPortEdit();

	PortForward validatedPort() const	{ return mValidPort;	}
};

#endif // DLGPORTEDIT_H
