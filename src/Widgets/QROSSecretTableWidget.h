#ifndef QROSSECRETTABLEWIDGET_H
#define QROSSECRETTABLEWIDGET_H

#include <QMap>
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
	QROSUserNameWidgetItem() : /*rosCachedPPPSecret(""), */pppActive("")
	{	}

	QPPPSecretMap pppSecretMap;
	ROSPPPActive pppActive;
};

class QROSServiceStatusCellItem : public QStyledWidgetItem
{
	ServiceState::Type m_serviceState;

public:
	QROSServiceStatusCellItem() : QStyledWidgetItem()
	{	}

	void setServiceState(ServiceState::Type st)
	{
		setText( ServiceState::readableString(m_serviceState = st) );
		updateStyle();
	}
	virtual const CellLook &getCellLook()override;
};

class QROSActiveStatusCellItem : public QStyledWidgetItem
{
	struct _times
	{
		QDateTime uptime;
		QDateTime downtime;
	};
	QMap<QString, _times> data;
	QString curRouter;
	QDateTime curUpTime;
	QDateTime curDwTime;

	void updateText();

public:
	QROSActiveStatusCellItem() : QStyledWidgetItem()
	{	}
	void setUptime(const QString &routerName, const QDateTime &uptime)
	{
		data[routerName].uptime = uptime;
		curRouter = routerName;
		curUpTime = uptime;
		updateText();
		updateStyle();
	}
	void setLastDowntime(const QString &routerName, const QDateTime &downtime)
	{
		data[routerName].downtime = downtime;
		if( downtime.isValid() && (!curDwTime.isValid() || (curDwTime < downtime)) )
			curDwTime = downtime;
		updateText();
		updateStyle();
	}
	void setCurrentDowntime(const QString &routerName, const QDateTime &downtime)
	{
		data[routerName].downtime = downtime;
		if( curRouter == routerName )
			curUpTime = QDateTime();
		updateText();
		updateStyle();
	}
//	void setTimes(const QString &routerName, const QDateTime &uptime, const QDateTime &downtime)
//	{
//		data[routerName].uptime = uptime;
//		data[routerName].downtime = downtime;
//		if( downtime.isValid() )
//			m_downtime = downtime;
//		updateText();
//		updateStyle();
//	}
	virtual const CellLook &getCellLook()override;
};

class QROSSecretTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	enum Columns
	{
		UserName,
		ClientCode,
		ServiceStatus,
		UserProfile,
		ActiveUserStatus,
		RemoteIP,
		ActiveRouter,
		ClientName,
		ClientAddress,
		ClientCity,
		ClientPhone,
		Installer,
		ClientEmail,
		ClientAnnotations,
		InstallAnnotations,
		TotalColumns
	};

private:
	QMap<QString, QROSUserNameWidgetItem *> m_userNameMap;
	QMap<QString, QROSUserNameWidgetItem *> m_secretIDMap;
	QMap<QString, QROSUserNameWidgetItem *> m_activeIDMap;
	QStringList m_usedStaticIPList;	// For the static IP delegate, to know IPs to hide.

	bool m_applyFilter;
	QString m_filterText;
	ServiceState::Type m_filterServiceState;
	Columns m_filterFields;
	int m_voipFilter;
	int m_portsFilter;
	int m_staticIpFilter;

	QROSUserNameWidgetItem *addNewRow(const QString &userName);

	void onROSSecretModReply(const ROSPPPSecret &rosPPPSecret);
	void onROSSecretDelReply(const QString &routerName, const QString &rosObjectID);

	void onROSActiveModReply(const ROSPPPActive &rosPPPActive);
	void onROSActiveDelReply(const QString &routerName, const QString &rosObjectID);

	void setupCellItem(int row, Columns col, const QString &cellText, bool editable);
	void setupServiceCellItem(int row, ServiceState::Type st);
	QROSActiveStatusCellItem *setupActiveStatusCellItem(int row);
	void setupRemoteIPCellItem(int row, const IPv4 &remoteIP, const IPv4 &staticIP);
	void setupRemoteIPCellItem(const QROSUserNameWidgetItem *userNameItem );

	QTableWidgetItem *item(int row, Columns col)					{ return QTableWidget::item(row, static_cast<int>(col));	}
	const QTableWidgetItem *item(int row, Columns col) const		{ return QTableWidget::item(row, static_cast<int>(col));	}
	void setItem(int row, Columns col, QTableWidgetItem *cellItem)	{ QTableWidget::setItem(row, static_cast<int>(col), cellItem);	}
	static void setupCellItemStyle(QTableWidgetItem *item, const CellLook &cellLook);
	void setupCellItemStyle(int row, Columns col, const CellLook &cellLook);

	bool shouldBeVisible(const QROSUserNameWidgetItem *userNameItem);
	void showRowIfValid(const QROSUserNameWidgetItem *userNameItem);

	void raiseWarning( const QString &info ) const;
	bool checkStringData(ROSPPPSecret &pppSecret, const QString &fieldName, const QString &text, std::function<bool(ROSPPPSecret &, const QString &)> setFnc) const;

	void changeUserProfile(QROSUserNameWidgetItem *userNameItem, const QString &newProfile);
	void changeMultipleProfiles(const QList<QROSUserNameWidgetItem*> &selectedList, const QString newProfile);
	void openThroughputDialog(int row);

public:
	explicit QROSSecretTableWidget(QWidget *papi = Q_NULLPTR);

	QList<int> findData(const QString &text, QList<Columns> columns, bool exactMatch);

	static QStringList columnsNames();
	void setColumnHidden(int col, bool hidden);

	QROSUserNameWidgetItem *userNameWidgetItem(int row);
	const QROSUserNameWidgetItem *userNameWidgetItem(int row) const;
	static QString createObjectIDKey(const ROSPPPSecret &rosPPPSecret);
	static QString createObjectIDKey(const QString &routerName, const QString &rosObjectID);
	QList<QROSUserNameWidgetItem*> selectedUsers();

	QString cellText(int row, Columns col) const;
	QString originalProfile(int row) const	{ return cellText(row, UserProfile); }
	QString currentIP(int row);

	void applyFilter(bool active);
	void filter(const QString &text, Columns col, ServiceState::Type filterStates, int voipFilter, int portsFilter, int staticIpFilter);

	void clear();
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void onROSDone(const QString &routerName, DataTypeID dataTypeID);
	void onConfigChanged();
	void exportUsersData();

	QStringList usedStaticIPs() const;
	QStringList staticIPs(int row) const;

	bool allowCellChange(const QModelIndex &index,const QString &newText);

	void disconnectUser(int row);
	void disconnectSelected();

	void deleteUser(const QString &userName, bool sure = false) const;
	void onCellDobleClic(QTableWidgetItem *item);
	void onConfigDataChanged();

	const ROSPPPSecret *rosPppSecret(const QString &userName);

signals:
	void editPPPUser(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);
	void showUserTraffic(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);
	void contextMenuRequested(const QPoint &point);

protected:
	virtual void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // QROSSECRETTABLEWIDGET_H
