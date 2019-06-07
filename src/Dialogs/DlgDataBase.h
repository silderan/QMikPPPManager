/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DLGDATABASE_H
#define DLGDATABASE_H

#include <QDialog>
#include <QList>

#include "../ConfigData/QConfigData.h"
#include "../ROSData/DataTypeID.h"
#include "../ROSData/ROSDataBasics.h"
#include "../ROSMultiConnectorManager.h"

class QDialogBase : public QDialog
{
public:
	explicit QDialogBase(QWidget *papi);

	void raiseWarning(const QString &info, const QString &field = QString()) const;

	template<typename T, typename R>
	bool setMemberData(const R &newFieldData, ROSDataBase &rosData, std::function<bool(T &, const R &)> setFnc, const R &fieldName = R()) const
	{
		Q_ASSERT( dynamic_cast<T *>(&rosData) );

		if( setFnc( static_cast<T &>(rosData), newFieldData) )
			return true;
		raiseWarning( rosData.lastError(), fieldName );
		return false;
	}

	template<typename T>
	bool setTextMember(const QString &newFieldData, ROSDataBase &rosData, std::function<bool(T &, const QString &)> setFnc, const QString &fieldName = QString()) const
	{
		return setMemberData<T, QString>( newFieldData, rosData, setFnc, fieldName );
	}

	template<typename T, typename R>
	bool updateMemberData(const R &newFieldData, ROSDataBase &rosData, std::function<const R &(T &)> getFnc, std::function<bool(T &, const R &)> setFnc, const R &fieldName = R()) const
	{
		Q_ASSERT( dynamic_cast<T *>(&rosData) );

		// With this, accepts texts if it's the same than the secrets'.
		// This makes things easier for automatically generated users without some data.
		// So, it just forces to be all well formed for new users or when modifying field data.
		if( !static_cast<T &>(rosData).rosObjectID().isEmpty() && (getFnc(static_cast<T&>(rosData)) == newFieldData) )
			return true;

		if( setFnc( static_cast<T&>(rosData), newFieldData) )
			return true;
		raiseWarning( static_cast<T&>(rosData).lastError(), fieldName );
		return false;
	}

	template<typename T>
	bool updateTextMember(const QString &newFieldData, ROSDataBase &rosData, std::function<const QString &(T &)> getFnc, std::function<bool(T &, const QString &)> setFnc, const QString &fieldName = QString()) const
	{
		return updateMemberData<T, QString>(newFieldData, rosData, getFnc, setFnc, fieldName);
	}
	virtual void onConfigChanged()	{	}
	QObjectList allChildren(QObject *papi);
	void setReadOnly(bool readOnly);
};

class QNewROSDataDialogBase : public QDialogBase
{

public:
	explicit QNewROSDataDialogBase(QWidget *papi) : QDialogBase(papi)
	{	}

	virtual void setROSData(ROSDataBase &rosData) = 0;
	virtual bool getROSData(ROSDataBase &rosData) const = 0;

	template <class T>
	void tryAccept()
	{
		T tmp("");
		if( getROSData(tmp) )
			accept();
	}

	bool exec(ROSDataBase &rosData);
};


class QDlgMultiDataBase : public QDialogBase
{
	Q_OBJECT

	QConfigData &m_configData;
	ROSMultiConnectManager &m_rosMultiConnectManager;
	DataTypeIDList m_dataTypeIDList;

protected:
	virtual void updateMultipleData(DataTypeIDList dataTypeIDList, const QString &routerName = QString());

public:
	QDlgMultiDataBase(QConfigData &configData, ROSMultiConnectManager &rosMultiConnectManager, QWidget *parent);

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

typedef QList<QDlgMultiDataBase*> QDlgMultiDataBasePList;

#endif // DLGDATABASE_H
