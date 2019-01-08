#include "QROSAPIUserLevelComboBox.h"

#include "../ROSData/ROSAPIUser.h"

QROSAPIUserLevelComboBox::QROSAPIUserLevelComboBox(QWidget *papi) : QComboBox(papi)
{
	addItems(ROSAPIUser::levelNames());
	connect( this, SIGNAL(currentIndexChanged(int)), this, SLOT(onLevelChanged(int)) );
}

void QROSAPIUserLevelComboBox::select(const QString &levelName)
{
	int i = findText( levelName );
	if( i != -1 )
		setCurrentIndex( i );
	else
		qWarning( "%s no encontrado", levelName.toLatin1().data() );
}

void QROSAPIUserLevelComboBox::onLevelChanged(int index)
{
	emit levelChanged( static_cast<ROSAPIUser::Level>(index) );
}


QWidget *QROSAPIUserLevelComboBoxDelegate::createEditor(QWidget *papi, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(option);
	Q_UNUSED(index);

	QROSAPIUserLevelComboBox *cb = new QROSAPIUserLevelComboBox(papi);
	cb->setFrame( false );
	return cb;
}

void QROSAPIUserLevelComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QROSAPIUserLevelComboBox *cb = static_cast<QROSAPIUserLevelComboBox*>(editor);
	cb->select(index.model()->data(index, Qt::EditRole).toString());
}

void QROSAPIUserLevelComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QROSAPIUserLevelComboBox *cb = static_cast<QROSAPIUserLevelComboBox*>(editor);
	model->setData(index, cb->currentLevelName(), Qt::EditRole);
}

void QROSAPIUserLevelComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(index);
	editor->setGeometry(option.rect);
}
