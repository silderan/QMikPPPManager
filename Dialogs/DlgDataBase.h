#ifndef DLGDATABASE_H
#define DLGDATABASE_H

#include <QDialog>
#include <QList>

#include "../ConfigData/QConfigData.h"
#include "../ROSData/DataTypeID.h"
#include "../ROSData/ROSDataBasics.h"
#include "../ROSMultiConnectorManager.h"

class DlgDataBase : public QDialog
{
	Q_OBJECT

	QConfigData &m_configData;
	ROSMultiConnectManager &m_rosMultiConnectManager;
	DataTypeIDList m_dataTypeIDList;

protected:
	virtual void updateMultipleData(DataTypeIDList dataTypeIDList, const QString &routerName = QString());

public:
	DlgDataBase(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent);

	ROSMultiConnectManager &rosMultiConnectManager()	{ return m_rosMultiConnectManager;	}

	QConfigData &configData() { return m_configData;	}

	virtual void onConfigDataChanged()	{	}
	virtual void onROSModReply(const ROSDataBase &rosData) = 0;
	virtual void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID) = 0;
	virtual void onROSDone(const QString &routerName, DataTypeID dataTypeID) = 0;
	virtual void clear() = 0;
	virtual void onLogued(const QString &routerName);
	virtual void onDisconnected(const QString &routerName);
};

typedef QList<DlgDataBase*> QDlgDataBasePList;

#endif // DLGDATABASE_H
