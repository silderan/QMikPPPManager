#ifndef QROSAPIUSERSGROUPCOMBOBOX_H
#define QROSAPIUSERSGROUPCOMBOBOX_H

#include <QStyledItemDelegate>
#include <QStringList>
#include <QComboBox>

class QROSAPIUsersGroupComboBox : public QComboBox
{
	Q_OBJECT

public:
	explicit QROSAPIUsersGroupComboBox(QWidget *parent = 0, const QStringList &groupsList = QStringList(), const QString &groupName = QString());
	~QROSAPIUsersGroupComboBox();

	int index(const QString &groupName)const;

	void select(const QString &groupName);

	void addGroup(const QString &groupName);
	void delGroup(const QString &groupName);

	QString groupName(int index) const;
	QString currentGroupName() const;

	void setup(const QStringList &groupsList, QString curGroupName = QString());

private slots:
	void onCurrentIndexChanged(int index);

signals:
	void newGroupSelected(QString groupName);
};

class QROSAPIUsersGroupComboBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QROSAPIUsersGroupComboBoxDelegate(QObject *papi = 0) : QStyledItemDelegate(papi)
	{	}

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};
#endif // QROSAPIUSERSGROUPCOMBOBOX_H
