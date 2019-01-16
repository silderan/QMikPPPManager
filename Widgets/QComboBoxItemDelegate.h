#ifndef QCOMBOBOXITEMDELEGAT_H
#define QCOMBOBOXITEMDELEGAT_H

#include <QStyledItemDelegate>
#include <QComboBox>

#include "../ROSMultiConnectorManager.h"
#include "../ConfigData/QConfigData.h"


class QComboBoxItemDelegated : public QStyledItemDelegate
{
	Q_OBJECT

	const QStringList *m_addList;
	const QStringList *m_skipList;
	bool m_makeEditable;
	ROSMultiConnectManager *m_multiConManager;
	DataTypeID m_dataTypeID;

public:
	QComboBoxItemDelegated(const QStringList *addList, bool editable, const QStringList *skipList, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(addList)
	  , m_skipList(skipList)
	  , m_makeEditable(editable)
	  , m_multiConManager(Q_NULLPTR)
	  , m_dataTypeID(DataTypeID::ErrorTypeID)
	{	}
	QComboBoxItemDelegated(ROSMultiConnectManager *multiConManager, DataTypeID dataTypeID, bool editable, const QStringList *skipList, QObject *papi) : QStyledItemDelegate(papi)
	  , m_addList(Q_NULLPTR)
	  , m_skipList(skipList)
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
		setupComboBox( cb, comboBoxItemList() );
		return cb;
	}

	virtual QStringList comboBoxItemList() const
	{
		QStringList rtn;
		if( m_addList != Q_NULLPTR )
		{
			foreach( QString s, *m_addList )
				if( (m_skipList == Q_NULLPTR) || !m_skipList->contains(s) )
					rtn.append(s);
		}
		else
		if( m_multiConManager != Q_NULLPTR )
		{
			ROSDataBasePList list = m_multiConManager->rosDataList(m_dataTypeID);
			foreach( const ROSDataBase *rosData, list )
			{
				QString txt = rosDataSelectableText( *rosData );
				if( !rtn.contains(txt) && (!m_skipList || !m_skipList->contains(txt)) )
					rtn.append( txt );
			}
		}
		return rtn;
	}
	virtual void setupComboBox(QComboBox *cb, const QStringList &list) const
	{
		cb->setEditable(m_makeEditable);
		cb->addItems(list);
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
			int i = cb->findData( index.data().toString() );

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
		model->setData(index, static_cast<QComboBox*>(editor)->currentText(), Qt::EditRole );
	}
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
	{
		Q_UNUSED(index);
		editor->setGeometry(option.rect);
	}
};

#endif // QCOMBOBOXITEMDELEGAT_H
