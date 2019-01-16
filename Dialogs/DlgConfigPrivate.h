#ifndef DLGCONFIGPRIVATE_H
#define DLGCONFIGPRIVATE_H

#include "../Widgets/QComboBoxItemDelegate.h"

typedef QComboBoxItemDelegated QProfileGroupNameDelegate;

class QROSProfileNameDelegate : public QComboBoxItemDelegated
{

public:
	QROSProfileNameDelegate(ROSMultiConnectManager *multiConManager, const QStringList *selectedProfiles, QObject *papi) :
		QProfileGroupNameDelegate( multiConManager, DataTypeID::PPPProfile, false, selectedProfiles, papi)
	{	}
	virtual QString rosDataSelectableText( const ROSDataBase &rosData ) const Q_DECL_OVERRIDE
	{
		return static_cast<const ROSPPPProfile&>(rosData).profileName();
	}
};

class QProfileTypeDelegate : public QProfileGroupNameDelegate
{

public:
	QProfileTypeDelegate(const QStringList *list, QObject *papi) : QProfileGroupNameDelegate(list, true, Q_NULLPTR, papi)
	{

	}

	virtual QStringList comboBoxItemList() const Q_DECL_OVERRIDE
	{
		return QStringList() << ClientProfileData::serviceCanceledGroupName() << QProfileGroupNameDelegate::comboBoxItemList();
	}
};


#endif // DLGCONFIGPRIVATE_H
