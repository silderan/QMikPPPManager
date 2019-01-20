#ifndef QFANCYCOMBOBOX_H
#define QFANCYCOMBOBOX_H

#include <QComboBox>

class QFancyComboBox : public QComboBox
{

public:
	explicit QFancyComboBox(QWidget *papi = Q_NULLPTR);

	virtual void setup(const QString &defaultValue, const QStringList &addList, const QStringList &skipList, const QString &currentSelected);
	virtual void setup(const QStringList &addList, const QString &currentSelected, bool addIfNecessary = false);
	virtual void updateList(const QStringList &addList, bool addIfNecessary = false);
	virtual void setup(const QStringList &addList) { addItems(addList);	}
	void selectText(const QString &text, bool addIfNecessary = false);
};

#endif // QFANCYCOMBOBOX_H
