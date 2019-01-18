#ifndef QCOMBOBOXITEMDELEGAT_H
#define QCOMBOBOXITEMDELEGAT_H

#include <QStyledItemDelegate>
#include <QComboBox>

#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"

class QDelegableComboBox  : public QComboBox
{

public:
	QDelegableComboBox(QWidget *papi)	: QComboBox(papi)
	{	}
	virtual void setup(const QString &defaultValue, const QStringList &addList, const QStringList &skipList, const QString &currentSelected)
	{
		clear();
		if( !defaultValue.isEmpty() )
			addItem( defaultValue );
		int i = -1;
		foreach( QString ip, addList )
		{
			if( !skipList.contains(ip) )
				addItem(ip);
			else
			if( currentSelected == ip )
			{
				addItem(ip);
			}
			if( ip == currentSelected )
				i = count() - 1;
		}
		if( count() )
		{
			if( i == -1 )
			{
				if( !defaultValue.isEmpty() )
					i = 0;
				else
				{
					i = count();
					addItem(currentSelected);
				}
			}
		}
		setCurrentIndex(i);
	}
};

class QComboBoxItemDelegatedBase : public QStyledItemDelegate
{
	QString m_defaultValue;
	bool m_comboBoxEditable;
	std::function<QStringList(int)> m_getAddList;
	std::function<QStringList(int)> m_getSkipList;
	std::function<QString(int)> m_getCurrentSelected;

public:
	QComboBoxItemDelegatedBase(	QObject *papi, QString defaultValue, bool comboBoxEditable,
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
		QDelegableComboBox *cb = new QDelegableComboBox(parent);
		cb->setEditable(m_comboBoxEditable);
		return cb;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		static_cast<QDelegableComboBox*>(editor)->setup( m_defaultValue, m_getAddList(index.row()), m_getSkipList(index.row()), m_getCurrentSelected(index.row()) );
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		if( index.data(Qt::EditRole).toString() != static_cast<QDelegableComboBox*>(editor)->currentText() )
			model->setData(index, static_cast<QDelegableComboBox*>(editor)->currentText());
	}
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);
		editor->setGeometry(option.rect);
	}
};

class QComboBoxItemDelegated : public QStyledItemDelegate
{

protected:
	const QStringList *m_addList;
	int m_addColumn;
	const QStringList *m_skipList;
	int m_skipColumn;
	bool m_makeEditable;
	ROSMultiConnectManager *m_multiConManager;
	DataTypeID m_dataTypeID;

public:
	QComboBoxItemDelegated(const QStringList *addList, bool editable, const QStringList *skipList, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(addList)
	  , m_addColumn(-1)
	  , m_skipList(skipList)
	  , m_skipColumn(-1)
	  , m_makeEditable(editable)
	  , m_multiConManager(Q_NULLPTR)
	  , m_dataTypeID(DataTypeID::ErrorTypeID)
	{	}
	QComboBoxItemDelegated(const QStringList *addList, bool editable, int skipColumn, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(addList)
	  , m_addColumn(-1)
	  , m_skipList(Q_NULLPTR)
	  , m_skipColumn(skipColumn)
	  , m_makeEditable(editable)
	  , m_multiConManager(Q_NULLPTR)
	  , m_dataTypeID(DataTypeID::ErrorTypeID)
	{	}
	QComboBoxItemDelegated(int addColumn, bool editable, int skipColumn, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(Q_NULLPTR)
	  , m_addColumn(addColumn)
	  , m_skipList(Q_NULLPTR)
	  , m_skipColumn(skipColumn)
	  , m_makeEditable(editable)
	  , m_multiConManager(Q_NULLPTR)
	  , m_dataTypeID(DataTypeID::ErrorTypeID)
	{	}
	QComboBoxItemDelegated(ROSMultiConnectManager *multiConManager, DataTypeID dataTypeID, bool editable, const QStringList *skipList, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(Q_NULLPTR)
	  , m_addColumn(-1)
	  , m_skipList(skipList)
	  , m_skipColumn(-1)
	  , m_makeEditable(editable)
	  , m_multiConManager(multiConManager)
	  , m_dataTypeID(dataTypeID)
	{
		m_multiConManager->requestAll(m_dataTypeID);
	}
	virtual QComboBox *createComboBox(QWidget *parent) const
	{
		return new QComboBox(parent);
	}
	QWidget *createEditor(QWidget *papi, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(option);
		Q_UNUSED(index);
		QStringList list;
		QComboBox *cb = createComboBox(papi);
		setupComboBox( cb, index );
		return cb;
	}

	virtual QStringList addList(const QModelIndex &index) const
	{
		QStringList rtn;
		QString currentText = index.data(Qt::EditRole).toString();
		if( m_addList != Q_NULLPTR )
			rtn = *m_addList;
		if( m_addColumn != -1 )
		{
			int row;
			for( row = index.model()->rowCount()-1; row >= 0; --row )
			{
				QString addText = index.model()->index(row, m_addColumn).data(Qt::EditRole).toString();
				if( !addText.isEmpty() && ((addText == currentText) || !rtn.contains(addText)) )
					rtn.append(addText);
			}
		}
		if( !currentText.isEmpty() && !rtn.contains(currentText) )
			rtn.prepend(currentText);
		return rtn;
	}
	virtual QStringList skipList(const QModelIndex &index) const
	{
		QStringList rtn;
		QString currentText = index.data(Qt::EditRole).toString();
		if( m_skipList != Q_NULLPTR )
		{
			rtn = *m_skipList;
			if( rtn.contains(currentText) )
				rtn.removeOne(currentText);
		}
		if( m_skipColumn != -1 )
		{
			int row;
			for( row = index.model()->rowCount()-1; row >= 0; --row )
			{
				QString delText = index.model()->index(row, m_skipColumn).data(Qt::EditRole).toString();
				if( !delText.isEmpty() && (delText != currentText) && !rtn.contains(delText) )
					rtn.append(delText);
			}
		}
		return rtn;
	}
	virtual QStringList comboBoxItemList(const QModelIndex &index) const
	{
		QStringList addList = this->addList(index);
		QStringList skipList = this->skipList(index);
		if( skipList.count() )
		{
			for( int i = skipList.count()-1; (i >= 0) && !addList.isEmpty(); --i )
				addList.removeOne(skipList[i]);
		}
		return addList;
	}
	virtual void setupComboBox(QComboBox *cb, const QModelIndex &index) const
	{
		cb->setEditable(m_makeEditable);
		cb->addItems(comboBoxItemList(index));
	}
	virtual QString rosDataSelectableText( const ROSDataBase &rosData ) const
	{
		return QString("%s:%s").arg( rosData.routerName(), rosData.rosObjectID() );
	}

	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		if( index.data().toString().count() )
		{
			QComboBox *cb = static_cast<QComboBox*>(editor);
			int i = cb->findData( index.data().toString(), Qt::DisplayRole );

			if( i == -1 )
			{
				i = cb->count();
				cb->addItem( index.data().toString() );
			}
			cb->setCurrentIndex( i );
		}
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		if( index.data(Qt::EditRole) != static_cast<QComboBox*>(editor)->currentText() )
			model->setData( index, static_cast<QComboBox*>(editor)->currentText(), Qt::EditRole );
	}
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);
		editor->setGeometry(option.rect);
	}
};

#endif // QCOMBOBOXITEMDELEGAT_H
