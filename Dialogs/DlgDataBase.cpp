#include "DlgDataBase.h"

void DlgDataBase::updateMultipleData(DataTypeIDList dataTypeIDList, const QString &routerName)
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

DlgDataBase::DlgDataBase(QWidget *parent, ROSMultiConnectManager &rosMultiConnectManager) : QDialog(parent)
  , m_rosMultiConnectManager(rosMultiConnectManager)
{

}

void DlgDataBase::setConfigData(QConfigData &configData)
{
	m_configData = configData;
	onConfigDataChanged();
}

void DlgDataBase::onLogued(const QString &routerName)
{
	updateMultipleData(m_dataTypeIDList, routerName);
}

void DlgDataBase::onDisconnected(const QString &routerName)
{
	foreach( DataTypeID dataTypeID, m_dataTypeIDList )
		onROSDelReply( routerName, dataTypeID, QString() );
}
