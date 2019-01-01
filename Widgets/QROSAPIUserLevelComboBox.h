#ifndef QROSAPIUSERLEVELCOMBOBOX_H
#define QROSAPIUSERLEVELCOMBOBOX_H

#include <QComboBox>
#include <QStyledItemDelegate>

#include "../ROSAPIUser.h"

class QROSAPIUserLevelComboBox : public QComboBox
{
Q_OBJECT

public:
	explicit QROSAPIUserLevelComboBox(QWidget *papi = Q_NULLPTR);

	inline void select(const ROSAPIUser::Level &level)	{ setCurrentIndex( level ); }
	void select(const QString &levelName);

	inline QString currentLevel() const	{ return currentText();	}

private slots:
	void onLevelChanged(int index);

signals:
	void levelChanged(ROSAPIUser::Level);
};

class QROSAPIUserLevelComboBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QROSAPIUserLevelComboBoxDelegate(QObject *papi = 0) : QStyledItemDelegate(papi)
	{	}

	QWidget *createEditor(QWidget *papi, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // QROSAPIUSERLEVELCOMBOBOX_H
