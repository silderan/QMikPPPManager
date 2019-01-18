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

	virtual QStringList addList(const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index)
		return QStringList() << ClientProfileData::serviceCanceledGroupName() << QProfileGroupNameDelegate::addList(index);
	}
};


#endif // DLGCONFIGPRIVATE_H
