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

DlgDataBase::DlgDataBase(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent)
	: QDialog(parent)
  , m_configData(configData)
  , m_rosMultiConnectManager(rosMultiConnectManager)
{

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
