#ifndef QROSSECRETTABLEWIDGET_H
#define QROSSECRETTABLEWIDGET_H

#include <QTableView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include "ROSData/ROSSecret.h"

class QROSSecretDataModel : public QStandardItemModel
{
	Q_OBJECT

	QMap<QString, ROSSecretData> m_rosSecretDataUserNameMap;
	QMap<QString, ROSSecretData> m_rosSecretDataObjectIPMap;

public:
	enum Columns
	{
		UserNameCol,
		ClientCodeCol,
		ClientPaymentStatusCol,
		UserProfileCol,
		ActiveUserStatusCol,
		StaticIPCol,
		ClientNameCol,
		ClientAddressCol,
		ClientCityCol,
		ClientPhoneCol,
		ClientInstallerCol,
		ClientCommercialCol,
		ClientEmailCol,
		ClientNeedsPublicIPCol,
		ClientAnnotationsCol,
		TotalColumns
	};

public:
	QROSSecretDataModel();
};

class QROSSecretTableWidget : public QTableView
{
	Q_OBJECT

public:
	explicit QROSSecretTableWidget(QWidget *parent = Q_NULLPTR);

protected:
	void setupRow(int row, const ROSSecretData &rosSecretData);
	int rowOf(const ROSSecretData &rosSecretData);
	ROSSecretData *getRosData(int row);

public:
	void onROSModReply(const ROSDataBase &rosData);
	void onROSDelReply(const QString &routerName, const QString &rosObjectID);
};

#endif // QROSSECRETTABLEWIDGET_H
