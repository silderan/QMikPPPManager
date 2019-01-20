#ifndef QCOMBOBOXITEMDELEGAT_H
#define QCOMBOBOXITEMDELEGAT_H

#include <QStyledItemDelegate>
#include <QComboBox>

#include "QFancyComboBox.h"
#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"

class QComboBoxItemDelegated : public QStyledItemDelegate
{
	QString m_defaultValue;
	bool m_comboBoxEditable;
	std::function<QStringList(int)> m_getAddList;
	std::function<QStringList(int)> m_getSkipList;
	std::function<QString(int)> m_getCurrentSelected;

public:
	QComboBoxItemDelegated(	QObject *papi, QString defaultValue, bool comboBoxEditable,
								std::function<QStringList(int)> getAddList,
								std::function<QStringList(int)> getSkipList,
								std::function<QString(int)> getCurrentSelected) : QStyledItemDelegate(papi)
	  , m_defaultValue(defaultValue)
	  , m_comboBoxEditable(comboBoxEditable)
	  , m_getAddList(getAddList)
	  , m_getSkipList(getSkipList)
	  , m_getCurrentSelected(getCurrentSelected)
	{	}

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(option);
		Q_UNUSED(index);
		QFancyComboBox *cb = new QFancyComboBox(parent);
		cb->setEditable(m_comboBoxEditable);
		return cb;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		static_cast<QFancyComboBox*>(editor)->setup( m_defaultValue, m_getAddList(index.row()), m_getSkipList(index.row()), m_getCurrentSelected(index.row()) );
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		if( index.data(Qt::EditRole).toString() != static_cast<QFancyComboBox*>(editor)->currentText() )
			model->setData(index, static_cast<QFancyComboBox*>(editor)->currentText());
	}
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);
		editor->setGeometry(option.rect);
	}
};

#endif // QCOMBOBOXITEMDELEGAT_H
