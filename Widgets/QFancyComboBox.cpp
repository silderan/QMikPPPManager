#include "QFancyComboBox.h"

QFancyComboBox::QFancyComboBox(QWidget *papi) : QComboBox(papi)
{

}

void QFancyComboBox::setup(const QString &defaultValue, const QStringList &addList, const QStringList &skipList, const QString &currentSelected)
{
	clear();
	if( !defaultValue.isEmpty() )
		addItem( defaultValue );
	int i = -1;
	foreach( QString t, addList )
	{
		if( t == currentSelected )
		{
			i = count();
			addItem(t);
		}
		else
		if( !skipList.contains(t) )
			addItem(t);
	}
	if( count() )
	{
		if( i == -1 )
		{
			if( !defaultValue.isEmpty() )
				i = 0;
			else
			if( !currentSelected.isEmpty() )
			{
				i = count();
				addItem(currentSelected);
			}
		}
		setCurrentIndex(i);
	}
}

void QFancyComboBox::setup(const QStringList &addList, const QString &currentSelected, bool addIfNecessary)
{
	clear();
	if( currentSelected.isEmpty() )
		return setup(addList);
	addItems(addList);
	return selectText(currentSelected, addIfNecessary);
}

void QFancyComboBox::updateList(const QStringList &addList, bool addIfNecessary)
{
	if( currentText().isEmpty() )
		return setup(addList);
	else
		return setup(addList, currentText(), addIfNecessary );
}

void QFancyComboBox::selectText(const QString &text, bool addIfNecessary)
{
	int i = findData(text, Qt::EditRole);
	if( i == -1 )
	{
		if( addIfNecessary )
		{
			i = count();
			addItem(text);
		}
		else
			return setCurrentText(text);
	}
	setCurrentIndex(i);
}
