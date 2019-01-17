#ifndef QSTATICIPV4COMBOBOXPROFILE_H
#define QSTATICIPV4COMBOBOXPROFILE_H

#include "../ConfigData/QConfigData.h"
#include "QComboBoxItemDelegate.h"

class QStaticIPv4ComboBoxDelegate : public QComboBoxItemDelegated
{
	QConfigData &m_configData;

public:
	QStaticIPv4ComboBoxDelegate(QConfigData &configData, const QStringList *usedStaticIPList, QObject *papi) : QComboBoxItemDelegated(Q_NULLPTR, false, usedStaticIPList, papi)
	  , m_configData(configData)
	{	}
	QStringList comboBoxItemList() const Q_DECL_OVERRIDE
	{
		return QStringList() << tr("Dinámica") << m_configData.staticIPv4RangeListMap().staticIPv4StringList();
	}
};

#endif // QSTATICIPV4COMBOBOXPROFILE_H
