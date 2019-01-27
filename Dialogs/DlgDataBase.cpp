#include "DlgDataBase.h"

#include <QMessageBox>

QDialogBase::QDialogBase(QWidget *papi) : QDialog(papi)
{
}

void QDialogBase::raiseWarning(const QString &info, const QString &field) const
{
	if( field.isEmpty() )
		QMessageBox::warning( const_cast<QDialogBase*>(this), windowTitle(), info );
	else
		QMessageBox::warning( const_cast<QDialogBase*>(this), windowTitle(), tr("El campo '%1' %2").arg(field, info) );
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

void QDlgMultiDataBase::updateMultipleData(DataTypeIDList dataTypeIDList, const QString &routerName)
{
	Q_ASSERT( children().count() );		// This function must be called when ui has been configured.

	m_dataTypeIDList = dataTypeIDList;
	foreach( DataTypeID dataTypeID, m_dataTypeIDList )
	{
		ROSDataBasePList dataList = m_rosMultiConnectManager.rosDataList(dataTypeID, routerName);
		if( dataList.count() )
		{
			foreach( const ROSDataBase *rosData, dataList )
				onROSModReply( *rosData );
		}
		else
			m_rosMultiConnectManager.requestAll(dataTypeID);
	}
}

QDlgMultiDataBase::QDlgMultiDataBase(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent)
	: QDialogBase(parent)
  , m_configData(configData)
  , m_rosMultiConnectManager(rosMultiConnectManager)
{

}

void QDlgMultiDataBase::onLogued(const QString &routerName)
{
	updateMultipleData(m_dataTypeIDList, routerName);
}

void QDlgMultiDataBase::onDisconnected(const QString &routerName)
{
	foreach( DataTypeID dataTypeID, m_dataTypeIDList )
		onROSDelReply( routerName, dataTypeID, QString() );
}
