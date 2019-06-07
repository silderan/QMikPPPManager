#ifndef QFANCYCOMBOBOX_H
#define QFANCYCOMBOBOX_H

#include <QComboBox>

class QFancyComboBox : public QComboBox
{
	bool m_hasDefaultData;

public:
	explicit QFancyComboBox(QWidget *papi = Q_NULLPTR);

	virtual void setup(const QString &defaultValueDescription, const QString &defaultValueData, const QStringList &addList, const QStringList &skipList, const QString &currentSelected);
	virtual void setup(const QStringList &addList, const QString &currentSelected, bool addIfNecessary = false);
	virtual void updateList(const QStringList &addList, bool addIfNecessary = false);
	virtual void setup(const QStringList &addList) { addItems(addList);	}
	QString currentText();
	void selectText(const QString &text, bool addIfNecessary = false);
};

#endif // QFANCYCOMBOBOX_H
