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
	QROSUserNameWidgetItem() : rosPPPSecret(""), rosPPPActive("")
	{	}

	ROSPPPSecret rosPPPSecret;
	ROSPPPActive rosPPPActive;
	QRouterIDMap rosPPPSecretIDMap;
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
	QStringList m_usedStaticIPList;	// For the static IP delegate, to know IPs to hide.

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

	QROSUserNameWidgetItem *userNameWidgetItem(int row);
	static QString createObjectIDKey(const ROSPPPSecret &rosPPPSecret);
	static QString createObjectIDKey(const QString &routerName, const QString &rosObjectID);

	void onROSSecretModReply(const ROSPPPSecret &rosPPPSecret);
	void onROSSecretDelReply(const QString &routerName, const QString &rosObjectID);

	void onROSActiveModReply(const ROSPPPActive &rosPPPActive);
	void onROSActiveDelReply(const QString &routerName, const QString &rosObjectID);

	void setupCellItem(int row, Columns col, const QString &cellText);
	void setupServiceCellItem(int row, ROSPPPSecret::ServiceState st);
	void setupActiveStatusCellItem(int row, const QDateTime &uptime, const QDateTime &downtime);
	void setupRemoteIPCellItem(int row, const IPv4 &remoteIP, const IPv4 &staticIP);

	QTableWidgetItem *item(int row, Columns col)				{ return QTableWidget::item(row, static_cast<int>(col));	}
	static void setupCellItemStyle(QTableWidgetItem *item, const CellLook &cellLook);
	void setupCellItemStyle(int row, Columns col, const CellLook &cellLook);

	bool shouldBeVisible(int row);
	void showRowIfValid(int row);

public:
	explicit QROSSecretTableWidget(QWidget *papi = Q_NULLPTR);
	void applyFilter();

	QString originalProfile(int row)	{ return row < rowCount() ? item(row, UserProfile)->text() : QString(); }

	void clear();
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void onROSDone(const QString &routerName, DataTypeID dataTypeID);
	void updateConfig();
};

#endif // QROSSECRETTABLEWIDGET_H
