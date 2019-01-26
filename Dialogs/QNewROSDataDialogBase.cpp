#include "QNewROSDataDialogBase.h"

#include <QMessageBox>

QNewROSDataDialogBase::QNewROSDataDialogBase(QWidget *papi) : QDialog(papi)
{
}

void QNewROSDataDialogBase::raiseWarning(const QString &info, const QString &field) const
{
	if( field.isEmpty() )
		QMessageBox::warning( const_cast<QNewROSDataDialogBase*>(this), windowTitle(), info );
	else
		QMessageBox::warning( const_cast<QNewROSDataDialogBase*>(this), windowTitle(), tr("El campo %1, %2").arg(field, info) );
}

bool QNewROSDataDialogBase::exec(ROSDataBase &rosData)
{
	setROSData(rosData);
	if( QDialog::exec() == QDialog::Accepted )
	{
		if( getROSData(rosData) )
			return true;
	}
	return false;
}
