#include "QROSAPIUsersGroupComboBox.h"

#include "../ROSMultiConnectorManager.h"

QROSAPIUsersGroupComboBox::QROSAPIUsersGroupComboBox(QWidget *parent, const QStringList &groupsList, const QString &groupName) : QComboBox(parent)
{
	if( !groupsList.isEmpty() )
		setup(groupsList, groupName);
	addItems( multiConnectionManager.rosAPIUsersGrupList() );
	connect( this, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)) );
}

QROSAPIUsersGroupComboBox::~QROSAPIUsersGroupComboBox()
{

}

int QROSAPIUsersGroupComboBox::index(const QString &groupName) const
{
	for( int i = 0; i < count(); ++i )
		if( itemText(i) == groupName )
			return i;

	qWarning("Grupo de usuario API de nombre %s no encontrado", groupName.toLatin1().data());
	return -1;
}

void QROSAPIUsersGroupComboBox::select(const QString &groupName)
{
	int i = index(groupName);
	if( i == -1 )
	{
		addItem(groupName);
		i = count()-1;
	}
	setCurrentIndex(i);
}

void QROSAPIUsersGroupComboBox::addGroup(const QString &groupName)
{
	addItem(groupName);
}

void QROSAPIUsersGroupComboBox::delGroup(const QString &groupName)
{
	int i = index(groupName);
	if( i >= 0 )
		removeItem(i);
}

QString QROSAPIUsersGroupComboBox::groupName(int index) const
{
	if( (index >= 0) && (index < count()) )
		return itemText(index);

	qWarning("Indice %d fuera de rango en el ComboBox de los grupos de usuarios API", index);
	return QString();
}

QString QROSAPIUsersGroupComboBox::currentGroupName() const
{
	return currentText();
}

void QROSAPIUsersGroupComboBox::onCurrentIndexChanged(int index)
{
	emit newGroupSelected( groupName(index) );
}

void QROSAPIUsersGroupComboBox::setup(const QStringList &groupsList, QString curGroupName)
{
	int i;

	if( curGroupName.isEmpty() )
		curGroupName = currentGroupName();

	blockSignals(true);
	clear();
	for( i = 0; i < groupsList.count(); ++i )
		addGroup(groupsList.at(i));

	if( !curGroupName.isEmpty() )
		select(curGroupName);

	blockSignals(false);
}

QWidget *QROSAPIUsersGroupComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);

	QROSAPIUsersGroupComboBox *cb = new QROSAPIUsersGroupComboBox(parent);
	cb->setFrame(false);
	return cb;
}

void QROSAPIUsersGroupComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QROSAPIUsersGroupComboBox *cb = static_cast<QROSAPIUsersGroupComboBox*>(editor);
	cb->select(index.model()->data(index, Qt::EditRole).toString());
}

void QROSAPIUsersGroupComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QROSAPIUsersGroupComboBox *cb = static_cast<QROSAPIUsersGroupComboBox*>(editor);
	model->setData(index, cb->currentGroupName(), Qt::EditRole);
}

void QROSAPIUsersGroupComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(index);
	editor->setGeometry(option.rect);
}
