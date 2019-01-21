#ifndef QCOMBOBOXITEMDELEGAT_H
#define QCOMBOBOXITEMDELEGAT_H

#include <QStyledItemDelegate>
#include <QComboBox>

#include "QFancyComboBox.h"
#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"

class QFancyItemDelegate : public QStyledItemDelegate
{

protected:
	std::function<QString(const QModelIndex &)> m_getInitialText;
	std::function<bool(const QModelIndex &,const QString &)> m_allowChange;

public:
	QFancyItemDelegate(	QObject *papi,
						std::function<bool(const QModelIndex &,const QString &)> allowChange,
						std::function<QString(const QModelIndex &)> getInitialText = [](const QModelIndex &index){return index.data(Qt::EditRole).toString();})
		: QStyledItemDelegate(papi)
	  , m_getInitialText(getInitialText)
	  , m_allowChange(allowChange)
	{	}

	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		setEditorText( editor, m_getInitialText(index) );
	}
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		QString txt = getEditorText(editor);
		if( index.data(Qt::EditRole).toString() != txt )
		{
			if( m_allowChange(index, txt) )
				model->setData(index, txt, Qt::EditRole);
		}
	}
	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);
		editor->setGeometry(option.rect);
	}
	virtual void setEditorText(QWidget *editor, const QString &text) const = 0;
	virtual QString getEditorText(QWidget *editor) const = 0;
};

class QComboBoxItemDelegated : public QFancyItemDelegate
{
	QString m_defaultValue;
	bool m_comboBoxEditable;
	std::function<QStringList(int)> m_getAddList;
	std::function<QStringList(int)> m_getSkipList;

public:
	QComboBoxItemDelegated(	QObject *papi, QString defaultValue, bool comboBoxEditable,
							std::function<QStringList(int)> getAddList,
							std::function<QStringList(int)> getSkipList,
							std::function<bool(const QModelIndex &,const QString &)> allowChange,
							std::function<QString(const QModelIndex &)> getInitialText = [](const QModelIndex &index){return index.data(Qt::EditRole).toString();})
		: QFancyItemDelegate(papi, allowChange, getInitialText)
	  , m_defaultValue(defaultValue)
	  , m_comboBoxEditable(comboBoxEditable)
	  , m_getAddList(getAddList)
	  , m_getSkipList(getSkipList)
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
		static_cast<QFancyComboBox*>(editor)->setup( m_defaultValue, m_getAddList(index.row()), m_getSkipList(index.row()), m_getInitialText(index) );
	}
	virtual void setEditorText(QWidget *editor, const QString &text) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(editor);
		Q_UNUSED(text);
	}
	virtual QString getEditorText(QWidget *editor) const Q_DECL_OVERRIDE
	{
		return static_cast<QFancyComboBox*>(editor)->currentText();
	}
};


#include <QLineEdit>

class QLineEditItemDelegated : public QFancyItemDelegate
{

public:
	using QFancyItemDelegate::QFancyItemDelegate;

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(option);
		Q_UNUSED(index);
		return new QLineEdit(parent);
	}
	virtual void setEditorText(QWidget *editor, const QString &text) const Q_DECL_OVERRIDE
	{
		static_cast<QLineEdit*>(editor)->setText( text );
	}
	virtual QString getEditorText(QWidget *editor) const Q_DECL_OVERRIDE
	{
		return static_cast<QLineEdit*>(editor)->text();
	}
};

#endif // QCOMBOBOXITEMDELEGAT_H
