#ifndef QROSSECRETTABLEWIDGET_H
#define QROSSECRETTABLEWIDGET_H

#include <QTableWidget>
#include <QTableWidgetItem>

#include "ROSData/ROSSecret.h"
#include "../ConfigData/TableCellLook.h"

class QROSUserNameWidgetItem : public QTableWidgetItem
{
public:
	QRouterIDMap rosPPPSecretIDMap;
	QString rosPPPActiveObjectID;
	IPv4 staticIP;
};

class QROSServiceStatusCellItem : public QTableWidgetItem
{

public:

};

class QROSActiveStatusCellItem : public QTableWidgetItem
{

public:
	QString preOnline;
	QString preOffline;
	QDateTime onlineTime;
	QDateTime lastOffline;
	void updateStyle();
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
		ClientPaymentStatus,
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
	bool isEmptyCellText(int row, Columns col)	{	return (item(row, col) == Q_NULLPTR) || item(row, col)->text().isEmpty();  }

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
