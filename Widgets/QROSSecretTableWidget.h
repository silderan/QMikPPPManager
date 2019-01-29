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
		Installer,
		ClientEmail,
		ClientAnnotations,
		InstallAnnotations,
		TotalColumns
	};

	union FilterStates
	{
		struct bits
		{
			int userNameBit:1;
		}m_bit;
		int m_bits;
		FilterStates() : m_bits(0)
		{	}
	};

private:
	QMap<QString, QROSUserNameWidgetItem *> m_userNameMap;
	QMap<QString, QROSUserNameWidgetItem *> m_secretIDMap;
	QMap<QString, QROSUserNameWidgetItem *> m_activeIDMap;
	QStringList m_usedStaticIPList;	// For the static IP delegate, to know IPs to hide.

	QString m_filterText;
	ServiceState::Type m_filterServiceState;
	FilterStates m_filterFields;

	QROSUserNameWidgetItem *addNewRow(const QString &userName);

	void onROSSecretModReply(const ROSPPPSecret &rosPPPSecret);
	void onROSSecretDelReply(const QString &routerName, const QString &rosObjectID);

	void onROSActiveModReply(const ROSPPPActive &rosPPPActive);
	void onROSActiveDelReply(const QString &routerName, const QString &rosObjectID);

	void setupCellItem(int row, Columns col, const QString &cellText, bool editable);
	void setupServiceCellItem(int row, ServiceState::Type st);
	void setupActiveStatusCellItem(int row, const QDateTime &uptime, const QDateTime &downtime);
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
	void applyFilter();

public:
	explicit QROSSecretTableWidget(QWidget *papi = Q_NULLPTR);

	static QStringList columnsNames();

	QROSUserNameWidgetItem *userNameWidgetItem(int row);
	const QROSUserNameWidgetItem *userNameWidgetItem(int row) const;
	static QString createObjectIDKey(const ROSPPPSecret &rosPPPSecret);
	static QString createObjectIDKey(const QString &routerName, const QString &rosObjectID);
	QList<QROSUserNameWidgetItem*> selectedUsers();

	QString cellText(int row, Columns col) const;
	QString originalProfile(int row) const	{ return cellText(row, UserProfile); }
	QString currentIP(int row);

	void filter(const QString &text, FilterStates filterBits, ServiceState::Type filterStates);

	void clear();
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, DataTypeID dataTypeID, const QString &rosObjectID);
	void onROSDone(const QString &routerName, DataTypeID dataTypeID);
	void onConfigChanged();
	void exportUsersData();

	QStringList usedStaticIPs() const;
	QStringList staticIPs(int row) const;

	bool allowCellChange(const QModelIndex &index,const QString &newText);

	void disconnectSelected();

	void deleteUser(const QString &userName, bool sure = false) const;
	void onCellDobleClic(QTableWidgetItem *item);
	void onConfigDataChanged();

signals:
	void editPPPUser(const QPPPSecretMap &pppSecretMap, const ROSPPPActive &pppActive);
	void contextMenuRequested(const QPoint &point);

protected:
	virtual void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // QROSSECRETTABLEWIDGET_H
