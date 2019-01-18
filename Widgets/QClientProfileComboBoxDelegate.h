#ifndef QCLIENTPROFILECOMBOBOXDELEGATE_H
#define QCLIENTPROFILECOMBOBOXDELEGATE_H

#include "../ConfigData/QConfigData.h"
#include "QComboBoxItemDelegate.h"

class QClientProfileComboBoxDelegate : public QComboBoxItemDelegated
{
	QConfigData &m_configData;

public:
	QClientProfileComboBoxDelegate(QConfigData &configData, QObject *papi) : QComboBoxItemDelegated(Q_NULLPTR, false, Q_NULLPTR, papi)
	  , m_configData(configData)
	{	}
	QStringList addList(const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		return m_configData.clientProfileMap().regularProfileNames();
	}
};
#endif // QCLIENTPROFILECOMBOBOXDELEGATE_H
