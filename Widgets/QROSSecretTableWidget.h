#ifndef QROSSECRETTABLEWIDGET_H
#define QROSSECRETTABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidgetItem>

#include "ROSData/ROSSecret.h"
#include "../ConfigData/TableCellLook.h"

class QStyledWidgetItem : public QTableWidgetItem
{
	CellLook m_cellLook;

public:
	QStyledWidgetItem(const QString &text = QString()) : QTableWidgetItem(text)
	{	}

	void setCellLook(const CellLook &cellLook)
	{
		m_cellLook = cellLook;
		updateStyle();
	}
	void updateStyle();
	virtual const CellLook &getCellLook() = 0;
};

class QROSUserNameWidgetItem : public QTableWidgetItem
{
public:
	QRouterIDMap rosPPPSecretIDMap;
	QString rosPPPActiveObjectID;
	IPv4 staticIP;
};

class QROSServiceStatusCellItem : public QStyledWidgetItem
{
	ROSPPPSecret::ServiceState m_serviceState;

public:
	QROSServiceStatusCellItem() : QStyledWidgetItem()
	{	}

	void setServiceState(ROSPPPSecret::ServiceState st)
	{
		setText( ROSPPPSecret::serviceStateString(m_serviceState = st) );
		updateStyle();
	}
	virtual const CellLook &getCellLook()override;
};

class QROSActiveStatusCellItem : public QStyledWidgetItem
{
	QDateTime m_uptime;
	QDateTime m_downtime;

	void updateText();
public:
	QROSActiveStatusCellItem() : QStyledWidgetItem()
	{	}
	void setUptime(const QDateTime &uptime)
	{
		m_uptime = uptime;
		updateText();
		updateStyle();
	}
	void setDowntime(const QDateTime &downtime)
	{
		m_uptime = QDateTime();
		m_downtime = downtime;
		updateText();
		updateStyle();
	}
	void setTimes(const QDateTime &uptime, const QDateTime &downtime)
	{
		m_uptime = uptime;
		if( downtime.isValid() )
			m_downtime = downtime;
		updateText();
		updateStyle();
	}
	virtual const CellLook &getCellLook()override;
};

class QROSSecretTableWidget : public QTableWidget
{
	Q_OBJECT

	QMap<QString, QROSUserNameWidgetItem *> m_userNameMap;
	QMap<QString, QROSUserNameWidgetItem *> m_secretIDMap;
	QMap<QString, QROSUserNameWidgetItem *> m_activeIDMap;

public:
	enum Columns
	{
		UserName,
		ClientCode,
		ServiceStatus,
		UserProfile,
		ActiveUserStatus,
		ActiveRouter,
		RemoteIP,
		ClientName,
		ClientAddress,
		ClientCity,
		ClientPhone,
		ClientInstaller,
		ClientEmail,
		ClientAnnotations,
		TotalColumns
	};
	QROSUserNameWidgetItem *addNewRow(const QString &userName);

private:
	static QString createObjectIDKey(const QString &routerName, const QString &rosObjectID);

	void onROSSecretModReply(const ROSPPPSecret &rosSecretData);
	void onROSSecretDelReply(const QString &routerName, const QString &rosObjectID);

	void onROSActiveModReply(const ROSPPPActive &rosSecretActive);
	void onROSActiveDelReply(const QString &routerName, const QString &rosObjectID);

	void setupCellItem(int row, Columns col, const QString &cellText);
	void setupServiceCellItem(int row, ROSPPPSecret::ServiceState st);
	void setupActiveStatusCellItem(int row, const QDateTime &uptime, const QDateTime &downtime);

public:
	explicit QROSSecretTableWidget(QWidget *papi = Q_NULLPTR);

	QTableWidgetItem *item(int row, Columns col)				{ return QTableWidget::item(row, static_cast<int>(col));	}
	static void setupCellItemStyle(QTableWidgetItem *item, const CellLook &cellLook);
	void setupCellItemStyle(int row, Columns col, const CellLook &cellLook);

	void clear();
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void onROSDone(const QString &routerName, DataTypeID dataTypeID);
	void updateConfig();
};

#endif // QROSSECRETTABLEWIDGET_H
