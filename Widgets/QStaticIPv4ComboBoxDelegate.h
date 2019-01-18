#ifndef QSTATICIPV4COMBOBOXPROFILE_H
#define QSTATICIPV4COMBOBOXPROFILE_H

#include "../ConfigData/QConfigData.h"
#include "QComboBoxItemDelegate.h"
#include "QRemoteIPCellItem.h"

class QStaticIPv4ComboBoxDelegate : public QComboBoxItemDelegated
{
	const QConfigData &m_configData;
	int m_originalClientProfileColumn;
	int m_staticIPColumn;

public:
	QStaticIPv4ComboBoxDelegate(const QConfigData &configData, int staticIPColumn, int originalClientProfileColumn, QObject *papi) : QComboBoxItemDelegated(Q_NULLPTR, false, staticIPColumn, papi)
	  , m_configData(configData)
	  , m_originalClientProfileColumn(originalClientProfileColumn)
	  , m_staticIPColumn(staticIPColumn)
	{	}
	QStringList comboBoxItemList(const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);

		QString clientProfileName = index.model()->index(index.row(), m_originalClientProfileColumn).data(Qt::EditRole).toString();
		QString clientProfileGroup = m_configData.clientProfileMap().groupName(clientProfileName);
		QStringList staticIPList = m_configData.staticIPv4RangeListMap().staticIPv4StringList(clientProfileGroup);

		QStringList usedIPs;
		for( int row = index.model()->rowCount(); row >= 0; --row )
		{
			Q_ASSERT( static_cast<QRemoteIPCellItem*>(index.model()->item) );
		}
		return QStringList() << ( tr("Dinámica") ) << staticIPList;
	}
};

#endif // QSTATICIPV4COMBOBOXPROFILE_H
